#include <Arduino.h>

// Pines motor
const int PIN_IN1 = 18;
const int PIN_IN2 = 19;

// Pines botones
const int PIN_BTN_SUBIR = 25;
const int PIN_BTN_BAJAR = 26;

// Pines finales de carrera (normalmente abiertos)
const int PIN_FC_ARRIBA = 32;
const int PIN_FC_ABAJO  = 33;

// Pin fotocelda (LDR)
const int PIN_LDR = 34;

// Umbrales de luz (AJUSTA SEGÚN TUS MEDIDAS)
const int UMBRAL_MANANA = 3800; // por encima de esto: consideramos "mucho sol"
const int UMBRAL_NOCHE  = 1500; // por debajo de esto: consideramos "muy oscuro"

// Estado de luz
enum EstadoLuz {
  LUZ_OSCURO,
  LUZ_INTERMEDIO,
  LUZ_CLARO
};

EstadoLuz estadoLuzActual  = LUZ_INTERMEDIO;
EstadoLuz estadoLuzAnterior = LUZ_INTERMEDIO;

// Estado de persiana (aproximado)
enum EstadoPersiana {
  POS_DESCONOCIDA,
  POS_ARRIBA,
  POS_ABAJO
};

EstadoPersiana estadoPersiana = POS_DESCONOCIDA;

// Movimiento automático por LDR
enum AccionAuto {
  AUTO_NINGUNA,
  AUTO_ABRIR_MANANA,
  AUTO_CERRAR_NOCHE
};

AccionAuto accionAuto = AUTO_NINGUNA;
bool autoEnMarcha = false;

unsigned long ultimoPrint = 0;

// Funciones auxiliares
void motorParar() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
}

void motorSubir() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
}

void motorBajar() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
}

void setup() {
  Serial.begin(115200);

  // Motor
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  motorParar();

  // Botones con pull-up interno
  pinMode(PIN_BTN_SUBIR, INPUT_PULLUP);
  pinMode(PIN_BTN_BAJAR, INPUT_PULLUP);

  // Finales de carrera con pull-up interno
  pinMode(PIN_FC_ARRIBA, INPUT_PULLUP);
  pinMode(PIN_FC_ABAJO, INPUT_PULLUP);

  // Fotocelda
  pinMode(PIN_LDR, INPUT);

  Serial.println("Sistema de persiana (manual + LDR solo amanecer/anochecer).");
}

void loop() {
  // ---- Lecturas básicas ----
  bool btnSubirPressed = (digitalRead(PIN_BTN_SUBIR) == LOW);
  bool btnBajarPressed = (digitalRead(PIN_BTN_BAJAR) == LOW);

  bool fcArribaActivado = (digitalRead(PIN_FC_ARRIBA) == LOW);
  bool fcAbajoActivado  = (digitalRead(PIN_FC_ABAJO) == LOW);

  int ldrValue = analogRead(PIN_LDR);

  // Actualizamos estado aproximado de persiana según finales de carrera
  if (fcArribaActivado && !fcAbajoActivado) {
    estadoPersiana = POS_ARRIBA;
    // Si estábamos subiendo en automático y ya llegó arriba, paramos
    if (autoEnMarcha && accionAuto == AUTO_ABRIR_MANANA) {
      motorParar();
      autoEnMarcha = false;
      accionAuto = AUTO_NINGUNA;
      Serial.println("Auto: llegada a ARRIBA (amanecer).");
    }
  } else if (fcAbajoActivado && !fcArribaActivado) {
    estadoPersiana = POS_ABAJO;
    // Si estábamos bajando en automático y ya llegó abajo, paramos
    if (autoEnMarcha && accionAuto == AUTO_CERRAR_NOCHE) {
      motorParar();
      autoEnMarcha = false;
      accionAuto = AUTO_NINGUNA;
      Serial.println("Auto: llegada a ABAJO (anochecer).");
    }
  }
  // Si ninguno está activado, mantenemos el último estado conocido
  // (no sabemos la posición exacta, pero nos basta para la lógica)

  // ---- Clasificamos la luz en 3 estados ----
  estadoLuzAnterior = estadoLuzActual;

  if (ldrValue > UMBRAL_MANANA) {
    estadoLuzActual = LUZ_CLARO;
  } else if (ldrValue < UMBRAL_NOCHE) {
    estadoLuzActual = LUZ_OSCURO;
  } else {
    estadoLuzActual = LUZ_INTERMEDIO;
  }

  // Debug cada 500 ms
  unsigned long ahora = millis();
  if (ahora - ultimoPrint > 500) {
    ultimoPrint = ahora;
    Serial.print("LDR: ");
    Serial.print(ldrValue);
    Serial.print("  Luz: ");
    if (estadoLuzActual == LUZ_CLARO) Serial.print("CLARO");
    else if (estadoLuzActual == LUZ_OSCURO) Serial.print("OSCURO");
    else Serial.print("INTERMEDIO");
    Serial.print("  Posicion: ");
    if (estadoPersiana == POS_ARRIBA) Serial.println("ARRIBA");
    else if (estadoPersiana == POS_ABAJO) Serial.println("ABAJO");
    else Serial.println("DESCONOCIDA");
  }

  // ---- PRIORIDAD: BOTONES (control manual) ----
  if (btnSubirPressed || btnBajarPressed) {
    // Cualquier pulsación de botón cancela movimiento automático
    if (autoEnMarcha) {
      Serial.println("Modo manual: cancelando movimiento automático.");
    }
    autoEnMarcha = false;
    accionAuto = AUTO_NINGUNA;

    if (btnSubirPressed && !fcArribaActivado) {
      motorSubir();
      // Serial.println("Subiendo (manual)...");
    } else if (btnBajarPressed && !fcAbajoActivado) {
      motorBajar();
      // Serial.println("Bajando (manual)...");
    } else {
      motorParar();
    }
  } else {
    // ---- SIN BOTONES: solo aquí puede actuar la fotocelda ----

    // Si no hay movimiento automático en curso, detectamos eventos de amanecer/anochecer
    if (!autoEnMarcha) {
      // Evento "amanecer": pasamos a LUZ_CLARO
      if (estadoLuzAnterior != LUZ_CLARO && estadoLuzActual == LUZ_CLARO) {
        Serial.println("Evento LDR: AMANECER detectado.");
        // Si NO está ya arriba, abrimos
        if (estadoPersiana != POS_ARRIBA && !fcArribaActivado) {
          Serial.println("Auto: abriendo persiana por amanecer.");
          autoEnMarcha = true;
          accionAuto = AUTO_ABRIR_MANANA;
          motorSubir();
        } else {
          Serial.println("Persiana ya está ARRIBA, no se mueve (amanecer).");
        }
      }

      // Evento "anochecer": pasamos a LUZ_OSCURO
      if (estadoLuzAnterior != LUZ_OSCURO && estadoLuzActual == LUZ_OSCURO) {
        Serial.println("Evento LDR: ANOCHECER detectado.");
        // Si NO está ya abajo, cerramos
        if (estadoPersiana != POS_ABAJO && !fcAbajoActivado) {
          Serial.println("Auto: cerrando persiana por anochecer.");
          autoEnMarcha = true;
          accionAuto = AUTO_CERRAR_NOCHE;
          motorBajar();
        } else {
          Serial.println("Persiana ya está ABAJO, no se mueve (anochecer).");
        }
      }
    }

    // Si hay un movimiento automático en marcha, lo mantenemos hasta el final de carrera
    if (autoEnMarcha) {
      if (accionAuto == AUTO_ABRIR_MANANA) {
        if (!fcArribaActivado) {
          motorSubir();
        } else {
          motorParar();
          autoEnMarcha = false;
          accionAuto = AUTO_NINGUNA;
          estadoPersiana = POS_ARRIBA;
          Serial.println("Auto: llegada a ARRIBA (amanecer).");
        }
      } else if (accionAuto == AUTO_CERRAR_NOCHE) {
        if (!fcAbajoActivado) {
          motorBajar();
        } else {
          motorParar();
          autoEnMarcha = false;
          accionAuto = AUTO_NINGUNA;
          estadoPersiana = POS_ABAJO;
          Serial.println("Auto: llegada a ABAJO (anochecer).");
        }
      }
    } else {
      // Sin botones y sin auto → motor parado
      motorParar();
    }
  }

  delay(20);
}