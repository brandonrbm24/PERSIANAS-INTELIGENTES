# 🌞 Sistema de Control de Persianas Inteligentes

¡Bienvenidos al proyecto **Sistema de Control de Persianas Inteligentes**!  
Este sistema permite **automatizar la apertura y cierre de persianas** mediante control **manual**, **remoto (IoT)** y **automático por luz**, integrando el uso del **microcontrolador ESP32** y una interfaz conectada a **Adafruit IO**.

El objetivo es crear una solución **inteligente, práctica y segura** para mejorar el control de iluminación natural en espacios interiores, combinando hardware, software y tecnologías IoT.

---

## 🧠 Descripción del Proyecto

El sistema está diseñado para permitir el **control de persianas** bajo tres modalidades:

- 🔘 **Manual local:** dos botones físicos (SUBIR / BAJAR).  
- 🌐 **Remoto:** comandos desde un dashboard en **Adafruit IO** (MQTT).  
- 🌅 **Automático por luz (LDR):** actúa solo en eventos de **amanecer** y **anochecer**.

A través del **ESP32**, el sistema lee un **sensor LDR** para identificar cambios significativos de luz ambiental y ejecutar la acción correspondiente:
- **Amanecer (mucha luz)** → abrir persiana  
- **Anochecer (muy poca luz)** → cerrar persiana  

Para garantizar seguridad, el recorrido se limita con **dos finales de carrera (normalmente abiertos)**:
- Tope superior
- Tope inferior

✅ **Regla de prioridad del sistema:**  
1) **Botones físicos** → 2) **Adafruit IO** → 3) **Automático (LDR)**

---

## 🎯 Objetivo General

Desarrollar un sistema automatizado de control de persianas basado en **ESP32** con conectividad **IoT (Adafruit IO)**, capaz de funcionar en modo manual, remoto y automático por luz, mejorando la eficiencia energética y la comodidad del usuario.

---

## 🎯 Objetivos Específicos

- Diseñar el hardware del sistema de persianas inteligentes.
- Implementar el control del motor mediante **L298N** y ESP32.
- Implementar botones físicos con prioridad sobre otros modos de control.
- Integrar **LDR** para detección de amanecer/anochecer (sin control continuo).
- Conectar el sistema a **Adafruit IO** para monitoreo y control remoto.
- Documentar el desarrollo del sistema con diagramas, evidencias y pruebas.

---

## ✅ Funcionalidades Implementadas

- [x] Control manual con **dos botones** (SUBIR / BAJAR)
- [x] Protección por **finales de carrera** superior e inferior (NO)
- [x] Control automático por luz:
  - [x] Apertura al **amanecer**
  - [x] Cierre al **anochecer**
- [x] Control remoto por **Adafruit IO** con comandos:
  - [x] `UP`
  - [x] `DOWN`
  - [x] `STOP`
- [x] Manejo de prioridades (manual > remoto > automático)

---

## 🧰 Componentes Utilizados

| Componente | Descripción |
|----------|-------------|
| ESP32 (30 pines) | Microcontrolador principal |
| Motor DC con motoreductor | Movimiento de la persiana |
| L298N | Puente H para control del motor |
| 2 pulsadores | Control manual (SUBIR/BAJAR) |
| 2 finales de carrera (NO) | Límite superior e inferior |
| LDR + resistencia | Sensor de luz |
| Protoboard | Montaje del circuito |
| Fuente externa | Alimentación del motor |

---

## 🔌 Conexiones Principales

> 📌 Nota: ESP32 y L298N deben compartir **GND común**.

| Elemento | GPIO ESP32 |
|-------|-----------|
| IN1 (L298N) | GPIO 18 |
| IN2 (L298N) | GPIO 19 |
| Botón SUBIR | GPIO 25 |
| Botón BAJAR | GPIO 26 |
| Final de carrera ARRIBA (NO) | GPIO 32 |
| Final de carrera ABAJO (NO) | GPIO 33 |
| LDR (analógico) | GPIO 34 |

📎 Esquemático y conexiones:  
- `diagrams/esquematico.png`  
- `diagrams/conexiones.png`  

---

## 🛠️ Implementación Paso a Paso

### 1️⃣ Montaje del hardware (pruebas)
1. Conectar motor al L298N (OUT1/OUT2).
2. Alimentar L298N con fuente externa (según el motor).
3. Conectar GND del L298N con GND del ESP32.
4. Conectar botones con `INPUT_PULLUP` (a GND).
5. Conectar finales de carrera (NO) con `INPUT_PULLUP` (a GND).
6. Conectar LDR como divisor de tensión hacia GPIO34.

📸 Evidencias:
- `media/circuito_pruebas.jpg`
- `media/montaje_protoboard.jpg`

### 2️⃣ Control manual
- Programación del control por botones (SUBIR/BAJAR) con paro por finales de carrera.
- Verificación de giro del motor y paro al soltar botón.

### 3️⃣ Lógica automática por LDR (solo 2 eventos al día)
- Lectura ADC del LDR.
- Definición de umbrales:
  - Amanecer (mucha luz)
  - Anochecer (poca luz)
- Activación por evento (cambio de estado), no control continuo.
- Si ya está arriba/abajo, no se mueve.

### 4️⃣ Comunicación IoT (Adafruit IO)
- Conexión WiFi del ESP32.
- Suscripción al feed `persiana`.
- Recepción de comandos remotos:
  - `UP`, `DOWN`, `STOP`
- Integración con la prioridad del sistema.

### 5️⃣ Pruebas y validación
- Pruebas individuales por módulos (motor, botones, finales, LDR, IoT).
- Pruebas integrales del sistema completo con montaje final.

📸 Evidencias:
- `media/maqueta.jpg`
- `media/montaje_final.jpg`

---

## 🌐 Adafruit IO

- **Feed de control:** `persiana`
- **Comandos soportados:**
  - `UP` → Subir
  - `DOWN` → Bajar
  - `STOP` → Parar

📌 Recomendación de dashboard:
- 3 botones tipo **Momentary Button**: SUBIR / BAJAR / STOP

---

## 👥 Integrantes del Equipo

| Nombre | Rol | Responsabilidad |
|--------|------|----------------|
| **María Daniela Jiménez** | Líder del Proyecto (PO) / Pruebas | Coordinación general, documentación, validación y pruebas. |
| **Katherine Cardona** | Scrum Master / Diseño | Diagramas UML, montaje físico y validación. |
| **Brandon Bueno** | Programador IoT | Desarrollo del código ESP32 e integración Adafruit IO. |
| **Juan José Osorio** | Documentación | Elaboración de documentos técnicos. |

---

## 🕐 Planificación y Reuniones

- 🗓️ **Inicio del proyecto:** 5 de septiembre de 2025  
- 🗓️ **Entrega final:** 28 de noviembre de 2025  
- 💬 **Reuniones semanales:** Jueves (seguimiento de avances)  
- 🧑‍🏫 **Sesiones de trabajo en clase:** Viernes  

---

## 🧩 Fases del Proyecto

| Fase | Fecha | Actividades principales |
|------|--------|--------------------------|
| **1. Análisis y Requerimientos** | 05 - 15 septiembre | Requerimientos, historias de usuario, casos de uso. |
| **2. Diseño del Sistema** | 16 - 30 septiembre | Diagramas UML, planificación del hardware. |
| **3. Compra y Ensamble** | 01 - 15 octubre | Materiales, montaje inicial, pruebas. |
| **4. Desarrollo del Código** | 16 - 31 octubre | Control ESP32, integración IoT, pruebas unitarias. |
| **5. Pruebas y Validación** | 01 - 20 noviembre | Pruebas integrales y ajustes. |
| **6. Entrega Final** | 21 - 28 noviembre | Documentación final y video demo. |

---

## 📜 Historias de Usuario Iniciales

**HU-01:**  
> Como usuario, quiero abrir y cerrar las persianas manualmente desde el panel web, para controlar la iluminación sin depender del modo automático.

**HU-02:**  
> Como usuario, quiero que las persianas se abran al amanecer y se cierren al anochecer, para automatizar el control diario.

**HU-03:**  
> Como administrador, quiero visualizar el estado de la persiana y el nivel de luz, para monitorear el sistema.

**HU-04:**  
> Como usuario, quiero detener la persiana en cualquier momento, para ajustarla según mi necesidad.

**HU-05:**  
> Como usuario, quiero que el sistema respete los finales de carrera, para evitar daños mecánicos.

---

## ⚙️ Roles del Equipo según Metodología Scrum

| Rol | Nombre | Funciones |
|------|--------|-----------|
| 🧭 **Product Owner (PO)** | María Daniela Jiménez | Define requerimientos, valida entregas y coordina el equipo. |
| ⚙️ **Scrum Master (SM)** | Katherine Cardona | Facilita reuniones y seguimiento del proceso. |
| 💻 **Dev Team** | Brandon Bueno y Juan José Osorio | Desarrollo, pruebas y documentación del sistema. |

---

## ✅ Definition of Ready (DoR)

Una historia está lista para desarrollarse cuando:
- Tiene descripción clara (Como [rol], quiero [acción], para [beneficio]).
- Se definieron criterios de aceptación.
- Está priorizada.
- No depende de otra historia pendiente.

---

## 🧩 Definition of Done (DoD)

Una historia está terminada cuando:
- El código está implementado y probado en ESP32.
- La funcionalidad está verificada en Adafruit IO.
- Se realizó commit y push.
- La documentación se actualizó (README + docs/).
- El equipo aprobó la historia.

---

## 🔗 Enlaces Importantes

  
- 🧩 **Casos de Uso:** [/Documentos/Analisis/CasosDeUso.pdf`](https://github.com/brandonrbm24/PERSIANAS-INTELIGENTES/blob/main/Casos_de_Uso_Persianas.pdf)
- 🤖 **diagrama de estados:** https://github.com/brandonrbm24/PERSIANAS-INTELIGENTES/blob/main/DIAGRAMA%20DE%20ESTADO.docx
- 🧠 **Diagrama de Clases:** [/Documentos/Analisis/DiagramaDeClases.drawio](https://lucid.app/lucidchart/93453029-d999-42b9-aec2-85431b73eb32/edit?viewport_loc=-2932%2C-861%2C4092%2C1872%2C0_0&invitationId=inv_52cca74a-0cbc-42f3-8211-74e5729efa3b)  
- 🔌 **Código Fuente:** `/Aplicacion/`  
- 🧾 **Historias de Usuario:** `/Documentos/Analisis/HistoriasDeUsuario.pdf`
- 📸 **Evidencias:** `media/`
- 📎 **Esquemático:** `diagrams/`

---

## 📈 Estado Actual del Proyecto

🟢 **Funcional y documentado**  
> El proyecto cuenta con control manual, automático por eventos de luz y control IoT mediante Adafruit IO, con evidencias de montaje, pruebas y documentación técnica.

---

## 🧾 Licencia

Este proyecto es de uso académico.  
Universidad del Valle – Asignatura: *Metodologías de Desarrollo de Software*.

---

**Universidad del Valle – 2025**  
👩‍💻 *Proyecto desarrollado por el equipo de Sistema de Control de Persianas Inteligentes.*
