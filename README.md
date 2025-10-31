# 🌞 Sistema de Control de Persianas Inteligentes

¡Bienvenidos al proyecto **Sistema de Control de Persianas Inteligentes**!  
Este sistema permite **automatizar la apertura y cierre de persianas** mediante sensores de luz y control manual a través de una interfaz web conectada a **Adafruit IO**, integrando el uso del **microcontrolador ESP32**.

Nuestro objetivo es crear una solución inteligente, eficiente y práctica para el control de iluminación natural en espacios interiores, combinando hardware y software con tecnologías IoT.

---

## 🧠 Descripción del Proyecto

El sistema está diseñado para permitir el **control manual y automático de persianas**, gestionando la luz ambiental y el confort del usuario.  
A través del **ESP32**, el sistema recibe datos de un **sensor LDR**, que mide la intensidad luminosa. Según los valores obtenidos, las persianas se abren o cierran automáticamente.  
El usuario también puede manejar el sistema de forma manual desde una **interfaz web**, sincronizada con **Adafruit IO**, que permite monitorear el estado y enviar comandos en tiempo real.

---

## 🎯 Objetivo General

Desarrollar un sistema automatizado de control de persianas basado en **ESP32** con conectividad **IoT (Adafruit IO)**, capaz de funcionar tanto en modo manual como automático, mejorando la eficiencia energética y la comodidad del usuario.

---

## 🎯 Objetivos Específicos

- Diseñar el hardware del sistema de persianas inteligentes.
- Implementar sensores de luz (LDR) para detectar la luminosidad ambiental.
- Programar el control del motor mediante ESP32.
- Conectar el sistema a Adafruit IO para monitoreo y control remoto.
- Implementar una interfaz web para visualización y gestión.
- Documentar el desarrollo del sistema con diagramas, historias de usuario y casos de uso.

---

## 👥 Integrantes del Equipo

| Nombre | Rol | Responsabilidad |
|--------|------|----------------|
| **María Daniela Jiménez** | Líder del Proyecto (PO) / Encargado de Pruebas  | Coordinación general, documentación, validación y pruebas funcionales y seguimiento de entregas. |
| **Katherine Cardona** | Diseñadora / Encargado de Pruebas| Diseño de diagramas UML y Montaje físico, validación y pruebas funcionales |
| **Brandon Bueno** | Programador IoT | Desarrollo del código en ESP32, integración con Adafruit IO. |
| **Juan José Osorio** | Documentación  | elaboración de documentos técnicos. |

---

## 🕐 Planificación y Reuniones

- 🗓️ **Inicio del proyecto:** 5 de septiembre de 2025  
- 🗓️ **Entrega final:** 28 de noviembre de 2025  
- 💬 **Reuniones semanales:** Todos los **jueves** (coordinación de avances)  
- 🧑‍🏫 **Sesiones de trabajo en clase:** Todos los **viernes**

---

## 🧩 Fases del Proyecto

| Fase | Fecha | Actividades principales |
|------|--------|--------------------------|
| **1. Análisis y Requerimientos** | 05 - 15 septiembre | Levantamiento de requerimientos, historias de usuario, casos de uso. |
| **2. Diseño del Sistema** | 16 - 30 septiembre | Diagramas UML (casos de uso, clases, flujo), planificación del hardware. |
| **3. Compra y Ensamble de Materiales** | 01 - 15 octubre | Adquisición de ESP32, sensores, motores y montaje inicial. |
| **4. Desarrollo del Código** | 16 - 31 octubre | Programación del ESP32, conexión con Adafruit IO, pruebas unitarias. |
| **5. Pruebas y Validación** | 01 - 20 noviembre | Pruebas integrales del sistema y ajustes. |
| **6. Entrega Final y Presentación** | 21 - 28 noviembre | Documentación completa, video de funcionamiento y entrega final. |

---

## 🚀 Tecnologías y Herramientas

| Tipo | Tecnología / Herramienta |
|------|--------------------------|
| Microcontrolador | ESP32 |
| Lenguaje de programación | C (PlatformIO / Visual Studio Code) |
| IDE | Visual Studio Code con extensión PlatformIO |
| Comunicación IoT | MQTT - Adafruit IO |
| Sensor | LDR (sensor de luz) |
| Actuador | Motor DC + módulo de control |
| Control manual | Botones físicos |
| Control remoto | Dashboard en Adafruit IO |
| Control de versiones | Git / GitHub |
| Diagramas | Draw.io / Lucidchart |
| Documentación | Markdown / PDF |

---

## 📜 Historias de Usuario Iniciales

**HU-01:**  
> *Como usuario, quiero abrir las persianas manualmente desde el panel web, para controlar la iluminación sin depender del modo automático.*

**HU-02:**  
> *Como usuario, quiero que las persianas se cierren automáticamente cuando haya poca luz, para mantener privacidad y confort.*

**HU-03:**  
> *Como administrador, quiero visualizar el estado actual de las persianas y el nivel de luz, para monitorear el sistema.*

**HU-04:**  
> *Como usuario, quiero programar horarios de apertura y cierre, para automatizar el control diario de las persianas.*

**HU-05:**  
> *Como usuario, quiero recibir notificaciones si hay un fallo en el sensor o motor, para poder intervenir rápidamente.*

---

## ⚙️ Roles del Equipo según Metodología Scrum

| Rol | Nombre | Funciones |
|------|--------|-----------|
| 🧭 **Product Owner (PO)** | María Daniela Jiménez | Define los requerimientos, valida entregas y coordina el equipo. |
| ⚙️ **Scrum Master (SM)** | Katherine Cardona | Facilita reuniones, garantiza cumplimiento de metodología. |
| 💻 **Development Team (Dev Team)** | Brandon Bueno y Juan José Osorio | Desarrollan, prueban y documentan el sistema físico y lógico. |

---

## ✅ Definition of Ready (DoR)

Una historia está **lista para desarrollarse** cuando:
- Tiene una descripción clara (formato “Como [rol], quiero [acción], para [beneficio]”).
- Se han definido los criterios de aceptación.
- Está priorizada en el tablero del proyecto.
- No depende de otra historia pendiente.

---

## 🧩 Definition of Done (DoD)

Una historia está **completamente terminada** cuando:
- El código ha sido implementado y probado en el ESP32.
- La funcionalidad está verificada en Adafruit IO.
- El commit y push fueron realizados correctamente.
- La documentación se actualizó en.........
- El equipo aprobó la historia en revisión.

---

## 🧱 Estructura de Issues y Tareas del Proyecto

**Fase 1: Análisis y Diseño**
- TASK-01: Identificación de requerimientos
- TASK-02: Elaboración de casos de uso
- TASK-03: Diseño del diagrama de clases
- TASK-04: Documentación inicial del proyecto

**Fase 2: Desarrollo del Sistema**
- HU-01: Control manual desde Adafruit IO  
- HU-02: Control automático por sensor de luz  
- HU-03: Notificación de fallos  
- TECH-01: Programación del ESP32  
- TECH-02: Integración con Adafruit IO  
- TECH-03: Comunicación MQTT  

**Fase 3: Pruebas y Entrega**
- TEST-01: Pruebas de hardware  
- TEST-02: Validación de conexión IoT  
- TEST-03: Ajustes finales y presentación  

---

## 🔗 Enlaces Importantes

  
- 🧩 **Casos de Uso:** [/Documentos/Analisis/CasosDeUso.pdf`](https://github.com/brandonrbm24/PERSIANAS-INTELIGENTES/blob/main/Casos_de_Uso_Persianas.pdf)
- 🤖 **diagrama de estados:** https://github.com/brandonrbm24/PERSIANAS-INTELIGENTES/blob/main/DIAGRAMA%20DE%20ESTADO.docx
- 🧠 **Diagrama de Clases:** [/Documentos/Analisis/DiagramaDeClases.drawio](https://lucid.app/lucidchart/93453029-d999-42b9-aec2-85431b73eb32/edit?viewport_loc=-2932%2C-861%2C4092%2C1872%2C0_0&invitationId=inv_52cca74a-0cbc-42f3-8211-74e5729efa3b)  
- 🔌 **Código Fuente:** `/Aplicacion/`  
- 🧾 **Historias de Usuario:** `/Documentos/Analisis/HistoriasDeUsuario.pdf`

---

## 📈 Estado Actual del Proyecto
🟢 *On Track*  
> El proyecto se encuentra en fase de **desarrollo del código y conexión IoT**, con avance continuo en los diagramas, documentación y despues pruebas iniciales del prototipo físico.

---

## 🧾 Licencia
Este proyecto es de uso académico. Universidad del Valle – Asignatura: *Metodologías de Desarrollo de Software.*

---

**Universidad del Valle – 2025**  
👩‍💻 *Proyecto desarrollado por el equipo de Sistema de Control de Persianas Inteligentes.*
