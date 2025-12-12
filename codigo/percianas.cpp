#include <Arduino.h>
#include <WiFi.h>
#include "AdafruitIO_WiFi.h"

/***** CONFIG - Cambia según tu red / Adafruit IO *****/
#define WIFI_SSID   "xxxxxxxx"
#define WIFI_PASS   "xxxxxxxx"
#define IO_USERNAME "xxxxxxxxx"
#define IO_KEY      "xxxxxxxxxx"
/*******************************************************/

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// ----------------------- FEEDS -----------------------
AdafruitIO_Feed *feedSubir = io.feed("subirp");
AdafruitIO_Feed *feedBajar = io.feed("bajarp");
AdafruitIO_Feed *feedLDR   = io.feed("ldr");
AdafruitIO_Feed *feedEstado = io.feed("estado_persiana");

// ----------------------- PINES -----------------------
const int PIN_IN1 = 18;
const int PIN_IN2 = 19;

const int PIN_FC_ARRIBA = 32;
const int PIN_FC_ABAJO  = 33;

// LDR
const int PIN_LDR = 34;   // ADC1 - Analógico

// ----------------------- VARIABLES -----------------------
bool remotoSubiendo = false;
bool remotoBajando  = false;

String estadoPersiana = "DESCONOCIDA";

// ----------------------- FUNCIONES MOTOR -----------------------
void motorSubir() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
}

void motorBajar() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
}

void motorParar() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
}

// ----------------------- CALLBACKS REMOTOS -----------------------
void onFeedSubir(AdafruitIO_Data *data) {
  String val = data->toString();
  Serial.println("Feed subir recibido: " + val);

  if (val == "ON") {
    remotoBajando = false;
    remotoSubiendo = true;
    Serial.println("Remoto: INICIAR SUBIR");
  } else {
    remotoSubiendo = false;
    Serial.println("Remoto: PARAR (subir OFF)");
  }
}

void onFeedBajar(AdafruitIO_Data *data) {
  String val = data->toString();
  Serial.println("Feed bajar recibido: " + val);

  if (val == "ON") {
    remotoSubiendo = false;
    remotoBajando = true;
    Serial.println("Remoto: INICIAR BAJAR");
  } else {
    remotoBajando = false;
    Serial.println("Remoto: PARAR (bajar OFF)");
  }
}

// ----------------------- SETUP -----------------------
void setup() {
  Serial.begin(115200);

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  pinMode(PIN_FC_ARRIBA, INPUT_PULLUP);
  pinMode(PIN_FC_ABAJO, INPUT_PULLUP);

  motorParar();

  Serial.print("Conectando a Adafruit IO...");
  io.connect();

  feedSubir->onMessage(onFeedSubir);
  feedBajar->onMessage(onFeedBajar);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" conectado!");
}

// ----------------------- LOOP -----------------------
void loop() {
  io.run();

  // -------------------- LDR --------------------
  int ldrValue = analogRead(PIN_LDR);
  feedLDR->save(ldrValue);

  String luz = (ldrValue > 2000) ? "CLARO" : "OSCURO";

  Serial.println("LDR: " + String(ldrValue) + "  Luz: " + luz);

  // ---------- SEGURIDAD: FIN DE CARRERA ----------
  if (digitalRead(PIN_FC_ARRIBA) == LOW) {
    remotoSubiendo = false;
    estadoPersiana = "ARRIBA";
    feedEstado->save("ARRIBA");
    motorParar();
    return;
  }

  if (digitalRead(PIN_FC_ABAJO) == LOW) {
    remotoBajando = false;
    estadoPersiana = "ABAJO";
    feedEstado->save("ABAJO");
    motorParar();
    return;
  }

  // ---------- CONTROL REMOTO MANTIENE PRIORIDAD ----------
  if (remotoSubiendo) {
    motorSubir();
    return;
  }

  if (remotoBajando) {
    motorBajar();
    return;
  }

  // ---------- MODO AUTOMÁTICO POR LDR ----------
  if (luz == "CLARO") {
    Serial.println("AUTO: SUBIR (CLARO)");
    motorSubir();
    return;
  }

  if (luz == "OSCURO") {
    Serial.println("AUTO: BAJAR (OSCURO)");
    motorBajar();
    return;
  }

  // ---------- SI NO HAY NADA ACTIVO → PARAR ----------
  motorParar();
}
