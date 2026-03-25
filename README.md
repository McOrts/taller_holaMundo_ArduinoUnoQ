# Taller: Hola Mundo con Arduino UNO Q

---

## 🔷 ¿Qué es el Arduino UNO Q?

El **Arduino UNO Q** es la evolución más moderna de la icónica placa Arduino UNO. Mantiene el factor de forma clásico (compatible con shields y accesorios existentes) pero incorpora un procesador de nueva generación con conectividad WiFi y Bluetooth integrados, más memoria y, como elemento estrella, una **matriz LED de 12×8** integrada en la propia placa.

Está basado en el microcontrolador **RP2350** de la Fundación Raspberry Pi, con arquitectura dual-core ARM Cortex-M33, lo que supone un salto significativo en potencia de cálculo respecto a generaciones anteriores de Arduino UNO.

> 📌 Esta placa es ideal para proyectos de IoT (Internet de las Cosas) que requieren conectividad inalámbrica y visualización de datos sin necesidad de componentes externos.

---

## 📋 Especificaciones Técnicas

| Característica            | Detalle                                      |
|---------------------------|----------------------------------------------|
| **Microcontrolador**      | RP2350 (Dual-core ARM Cortex-M33 @ 150 MHz)  |
| **Memoria Flash**         | 4 MB                                         |
| **SRAM**                  | 520 KB                                       |
| **Voltaje de operación**  | 3.3V / 5V (tolerante a 5V en pines I/O)      |
| **Voltaje de entrada**    | 7–12 V (Jack DC) / 5V (USB-C)                |
| **Pines digitales I/O**   | 14 (6 con PWM)                               |
| **Pines analógicos**      | 6 (resolución 12 bits)                       |
| **Corriente máx. por pin**| 20 mA                                        |
| **WiFi**                  | 802.11 b/g/n (2.4 GHz)                       |
| **Bluetooth**             | Bluetooth 5.0 / BLE                          |
| **Conector USB**          | USB-C                                        |
| **Matriz LED integrada**  | 12 × 8 LEDs (96 LEDs en total)               |
| **UART**                  | 1 (hardware) + 1 (USB-CDC)                   |
| **SPI / I2C**             | 1 / 1                                        |
| **Temperatura operación** | −40 °C a +85 °C                              |
| **Dimensiones**           | 68.6 × 53.4 mm (compatible UNO R3)           |

---

## ✨ Características Principales

- 🔌 **USB-C** — Conector moderno y reversible para programación y alimentación
- 📶 **WiFi integrado** — Conectividad 802.11 b/g/n para proyectos IoT sin shields adicionales
- 🔷 **Bluetooth 5.0 / BLE** — Comunicación inalámbrica de corto alcance
- 💡 **Matriz LED 12×8** — Pantalla de 96 LEDs integrada para mostrar texto, iconos y animaciones
- ⚡ **Procesador dual-core** — Mayor potencia: dos núcleos ARM Cortex-M33 a 150 MHz
- 🧠 **Más memoria** — 520 KB de SRAM y 4 MB Flash, suficiente para proyectos complejos
- 🔒 **Seguridad hardware** — Soporte para arranque seguro y cifrado

---

## 🗺️ Diagrama de Conectividad y Puertos

```
                    ┌─────────────────────────────────────────────────────┐
                    │                  ARDUINO UNO Q                      │
                    │                                                     │
  ┌─ ALIMENTACIÓN ──┤ IOREF  RST  3V3  5V  GND  GND  VIN               │
  │                 │  [■]   [■]  [■]  [■]  [■]  [■]  [■]               │
  │                 │                                                     │
  │ ┌─ ANALÓGICO ───┤  A0    A1   A2   A3   A4   A5                      │
  │ │               │  [■]   [■]  [■]  [■]  [■]  [■]                     │
  │ │               │        (también SDA) (también SCL)                 │
  │ │               │                                                     │
  │ │               │   ╔═══════════════════════════╗                    │
  │ │               │   ║   MATRIZ LED 12 × 8       ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ║  ● ● ● ● ● ● ● ● ● ● ● ● ║                    │
  │ │               │   ╚═══════════════════════════╝                    │
  │ │               │                                                     │
  │ │               │  [DC JACK 2.1mm]         [USB-C]  [RESET]          │
  │ │               │                                                     │
  │ └─ DIGITAL ─────┤  D0/RX  D1/TX  D2  D3~  D4  D5~  D6~  D7          │
  │                 │   [■]    [■]   [■]  [■]  [■]  [■]  [■]  [■]        │
  └─────────────────┤  D8   D9~  D10~  D11~/MOSI  D12/MISO  D13/SCK     │
                    │  [■]  [■]   [■]     [■]        [■]       [■]       │
                    │                              LED (D13) ──┘          │
                    │  [ICSP: MISO MOSI SCK RST VCC GND]                  │
                    └─────────────────────────────────────────────────────┘

  ~ = Pin con PWM (modulación de ancho de pulso)
```

### Mapa de Pines Detallado

#### Pines Digitales

| Pin  | Etiqueta       | Función Principal | Funciones Alternativas         |
|------|----------------|-------------------|--------------------------------|
| D0   | RX             | Digital I/O       | UART Recepción                 |
| D1   | TX             | Digital I/O       | UART Transmisión               |
| D2   | D2             | Digital I/O       | Interrupción externa (INT0)    |
| D3   | ~D3            | Digital I/O + PWM | Interrupción externa (INT1)    |
| D4   | D4             | Digital I/O       | —                              |
| D5   | ~D5            | Digital I/O + PWM | —                              |
| D6   | ~D6            | Digital I/O + PWM | —                              |
| D7   | D7             | Digital I/O       | —                              |
| D8   | D8             | Digital I/O       | —                              |
| D9   | ~D9            | Digital I/O + PWM | —                              |
| D10  | ~D10/SS        | Digital I/O + PWM | SPI Slave Select               |
| D11  | ~D11/MOSI      | Digital I/O + PWM | SPI Master Out / Slave In      |
| D12  | D12/MISO       | Digital I/O       | SPI Master In / Slave Out      |
| D13  | D13/SCK/LED    | Digital I/O       | SPI Clock / LED integrado      |

#### Pines Analógicos

| Pin  | Función alternativa | Descripción                         |
|------|---------------------|-------------------------------------|
| A0   | GPIO                | Entrada analógica 0 (0–3.3V)        |
| A1   | GPIO                | Entrada analógica 1 (0–3.3V)        |
| A2   | GPIO                | Entrada analógica 2 (0–3.3V)        |
| A3   | GPIO                | Entrada analógica 3 (0–3.3V)        |
| A4   | SDA (I²C)           | Datos I²C / Entrada analógica 4     |
| A5   | SCL (I²C)           | Reloj I²C / Entrada analógica 5     |

#### Pines de Alimentación

| Pin    | Voltaje | Descripción                                      |
|--------|---------|--------------------------------------------------|
| VIN    | 7–12 V  | Alimentación externa (Jack DC o este pin)        |
| 5V     | 5 V     | Salida regulada 5V (máx. 500 mA desde USB)       |
| 3V3    | 3.3 V   | Salida regulada 3.3V (máx. 300 mA)               |
| GND    | 0 V     | Tierra / Masa (hay 2 pines GND en la fila)       |
| IOREF  | —       | Referencia de tensión de los pines I/O           |
| RST    | —       | Reinicio del microcontrolador (activo en LOW)    |

#### Interfaz ICSP (In-Circuit Serial Programming)

```
   MISO ─── [●] [●] ─── VCC
   SCK  ─── [●] [●] ─── MOSI
   RST  ─── [●] [●] ─── GND
```

---

---

# 📖 Manual: Weather Forecast en Matriz LED

## Introducción

Este manual describe paso a paso cómo ejecutar el ejemplo **"Weather forecast on LED matrix"** de Arduino App Lab en una placa **Arduino UNO Q**. Al finalizar, tendrás un dispositivo conectado a internet que consulta la previsión meteorológica de **Madrid** y la muestra en la matriz LED integrada de 12×8.

```
          ┌──────────────────────────────────────────────┐
          │  FLUJO COMPLETO DEL PROYECTO                 │
          │                                              │
          │  ① Conectar placa al PC   →  Cable USB-C     │
          │  ② Identificar puerto     →  COM3 / ttyACM0  │
          │  ③ Instalar Arduino App Lab                  │
          │  ④ Abrir ejemplo Weather Forecast            │
          │  ⑤ Cambiar ciudad a "Madrid"                 │
          │  ⑥ Configurar WiFi y API Key                 │
          │  ⑦ Subir a la placa      →  ¡Ver el tiempo!  │
          └──────────────────────────────────────────────┘
```

---

## Requisitos Previos

### Hardware

| Componente               | Cantidad | Descripción                         |
|--------------------------|----------|-------------------------------------|
| Arduino UNO Q            | 1        | La placa principal del proyecto     |
| Cable USB-C a USB-A      | 1        | Para programar y alimentar la placa |
| Ordenador (PC/Mac/Linux) | 1        | Para escribir y subir el código     |

> ⚠️ **Importante**: Usa un cable **USB de datos** (no solo de carga). Muchos cables de móvil económicos solo transmiten energía. Si el ordenador no detecta la placa, prueba con otro cable.

### Software

- **Arduino IDE 2.x** (gratuito) — [descargar aquí](https://www.arduino.cc/en/software)
- **Paquete de placa Arduino UNO Q** — se instala desde el IDE
- **Bibliotecas**: `WiFiS3`, `ArduinoHttpClient`, `ArduinoJson`, `Arduino_LED_Matrix`
- **Cuenta en OpenWeatherMap** (gratuita) — [registrarse aquí](https://home.openweathermap.org/users/sign_up) para obtener una API Key

---

## Paso 1: Conectar la Placa al Ordenador

### 1.1 Conexión física

```
                              Cable USB-C ↔ USB-A
                                    │
   ┌──────────────┐                 │                 ┌──────────────────┐
   │  ORDENADOR   │                 │                 │  ARDUINO UNO Q   │
   │              ├─── [USB-A] ═════╪═════ [USB-C] ───┤                  │
   │   Windows /  │                 │                 │  LED de          │
   │   macOS /    │                 │                 │  alimentación    │
   │   Linux      │                 │                 │  se ilumina ✓    │
   └──────────────┘                                   └──────────────────┘
```

**Pasos:**

1. Toma el cable USB-C y conéctalo al puerto **USB-C** de la placa Arduino UNO Q
2. Conecta el otro extremo al puerto USB de tu ordenador
3. La placa se encenderá automáticamente:
   - El **LED verde de alimentación** (PWR) se iluminará
   - La **matriz LED** mostrará brevemente una animación de inicio
4. El sistema operativo reconocerá el dispositivo e instalará los drivers automáticamente

### 1.2 Señales visuales de estado

```
Estado de los LEDs al conectar:

  PWR (verde)  ── Siempre encendido mientras hay alimentación
  L / D13      ── Parpadea durante la carga de un sketch
  RX           ── Parpadea al recibir datos por serie
  TX           ── Parpadea al enviar datos por serie
```

---

## Paso 2: Identificar el Puerto USB

Es necesario saber a qué puerto se ha conectado la placa para poder comunicarse con ella desde el IDE.

### En Windows

1. Haz clic derecho en el botón **Inicio** → selecciona **"Administrador de dispositivos"**
2. Expande la sección **"Puertos (COM y LPT)"**
3. Busca una entrada como **"Arduino UNO Q (COMx)"**

```
  Administrador de dispositivos
  └── 📂 Puertos (COM y LPT)
      ├── Puerto de comunicaciones (COM1)
      └── Arduino UNO Q (COM3)  ◄── Este es tu Arduino
                       ^^^
                  Anota este número
```

> 💡 **Truco**: Desconecta y vuelve a conectar la placa para identificar cuál puerto aparece y desaparece.

### En macOS

1. Abre la **Terminal** (Cmd+Espacio → escribe "Terminal" → Enter)
2. Ejecuta:
   ```bash
   ls /dev/tty.*
   ```
3. Busca algo como `/dev/tty.usbmodem14201`:

```bash
$ ls /dev/tty.*
/dev/tty.Bluetooth-Incoming-Port
/dev/tty.usbmodem14201          ◄── Este es tu Arduino
```

> 💡 También puedes ejecutar `ls /dev/cu.*` para ver el mismo listado con otro prefijo.

### En Linux

1. Abre una **Terminal**
2. Ejecuta:
   ```bash
   ls /dev/ttyACM* /dev/ttyUSB*
   ```
3. Busca `/dev/ttyACM0` o `/dev/ttyUSB0`:

```bash
$ ls /dev/ttyACM*
/dev/ttyACM0   ◄── Este es tu Arduino
```

> ⚠️ En Linux puede ser necesario agregar tu usuario al grupo `dialout`:
> ```bash
> sudo usermod -a -G dialout $USER
> ```
> Después reinicia la sesión para que tenga efecto.

---

## Paso 3: Instalar Arduino App Lab (Arduino IDE 2.x)

### 3.1 Descargar e instalar el IDE

```
  https://www.arduino.cc/en/software
          │
          ▼
  ┌────────────────────────────────────────────────────────┐
  │  Arduino Software  │  Downloads                       │
  │                    │                                  │
  │  Arduino IDE 2.x   │  [Windows  ] ← Descargar        │
  │  (Recomendado)     │  [macOS    ] ← Descargar        │
  │                    │  [Linux    ] ← Descargar        │
  └────────────────────────────────────────────────────────┘
```

1. Visita [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Descarga el instalador para tu sistema operativo
3. Ejecuta el instalador y sigue los pasos (acepta instalar drivers USB cuando se solicite)
4. Abre **Arduino IDE 2**

### 3.2 Instalar el soporte para Arduino UNO Q

1. En el IDE, ve a **Herramientas → Placa → Gestor de Placas**
2. En el buscador, escribe **"Arduino UNO Q"** o **"RP2350"**
3. Localiza el paquete **"Arduino UNO Q Boards"** y haz clic en **"Instalar"**

```
  Gestor de Placas
  ┌─────────────────────────────────────────────────────┐
  │  Buscar: [Arduino UNO Q              ]              │
  │                                                     │
  │  ┌─────────────────────────────────────────────┐   │
  │  │  Arduino UNO Q Boards                       │   │
  │  │  by Arduino                                 │   │
  │  │  Versión 1.0.0                              │   │
  │  │                          [Instalar]         │   │
  │  └─────────────────────────────────────────────┘   │
  └─────────────────────────────────────────────────────┘
```

> ⏳ La descarga puede tardar varios minutos dependiendo de tu conexión.

### 3.3 Instalar las bibliotecas necesarias

1. Ve a **Sketch → Incluir Biblioteca → Gestionar Bibliotecas**
2. Busca e instala cada una de estas bibliotecas:

| Biblioteca           | Autor    | Para qué sirve                        |
|----------------------|----------|---------------------------------------|
| `WiFiS3`             | Arduino  | Conectividad WiFi en Arduino UNO Q    |
| `ArduinoHttpClient`  | Arduino  | Realizar peticiones HTTP              |
| `ArduinoJson`        | Benoit Blanchon | Analizar respuestas JSON       |
| `Arduino_LED_Matrix` | Arduino  | Controlar la matriz LED integrada     |

```
  Gestionar Bibliotecas
  ┌───────────────────────────────────────────────────────┐
  │  Buscar: [ArduinoJson                    ]           │
  │  Tipo:   [Todo         ▼]                            │
  │                                                      │
  │  ArduinoJson by Benoit Blanchon                      │
  │  Versión 7.x.x                                       │
  │                                        [Instalar]    │
  └───────────────────────────────────────────────────────┘
```

---

## Paso 4: Obtener una API Key de OpenWeatherMap

El ejemplo necesita una clave gratuita de [OpenWeatherMap](https://openweathermap.org) para obtener los datos del tiempo.

1. Ve a [https://home.openweathermap.org/users/sign_up](https://home.openweathermap.org/users/sign_up)
2. Crea una cuenta gratuita
3. Una vez registrado, ve a **"My API keys"** en tu perfil
4. Copia tu clave API (una cadena larga de letras y números)

```
  Mi perfil de OpenWeatherMap
  ┌─────────────────────────────────────────────────────────┐
  │  API keys                                              │
  │                                                        │
  │  Nombre          Clave                                 │
  │  ─────────────────────────────────────────────────     │
  │  Default         abc123def456ghi789jkl012mno345pq  ← Copiar│
  │                                                        │
  └─────────────────────────────────────────────────────────┘
```

> ⏰ **Nota**: Las claves nuevas pueden tardar hasta **2 horas** en activarse.

---

## Paso 5: Abrir el Ejemplo "Weather Forecast on LED Matrix"

### Desde Arduino App Lab (navegador)

1. Ve a [https://lab.arduino.cc](https://lab.arduino.cc)
2. Inicia sesión con tu cuenta Arduino
3. En la sección **"Examples"** busca **"Weather forecast on LED matrix"**
4. Haz clic en **"Open in IDE"**

### Desde este repositorio (recomendado)

El ejemplo con comentarios en español ya está listo en la carpeta [`weather_forecast_led_matrix/`](./weather_forecast_led_matrix/):

```
weather_forecast_led_matrix/
├── weather_forecast_led_matrix.ino   ← Código principal (abrir esto)
└── arduino_secrets.h                 ← Credenciales WiFi y API Key
```

1. Abre Arduino IDE
2. Ve a **Archivo → Abrir**
3. Navega hasta la carpeta `weather_forecast_led_matrix/`
4. Selecciona `weather_forecast_led_matrix.ino`

---

## Paso 6: Configurar el Ejemplo

### 6.1 Configurar WiFi y API Key

Abre el archivo `arduino_secrets.h` (aparece como segunda pestaña en el IDE):

```cpp
// Reemplaza estos valores con los tuyos:
#define SECRET_SSID    "NombreDeTuRedWiFi"     // ← Nombre de tu red
#define SECRET_PASS    "TuContraseñaWiFi"      // ← Contraseña
#define SECRET_API_KEY "TuClaveDeOpenWeather"  // ← Tu API Key
```

### 6.2 Cambiar la ciudad a Madrid

En el archivo `weather_forecast_led_matrix.ino`, busca esta línea (ya está configurada a Madrid en este repositorio):

```cpp
// Busca esto en el ejemplo original:
String city = "London";

// Y cámbialo a esto:
String city = "Madrid";
```

> 📍 Para mayor precisión (evitar confusión con otras ciudades llamadas "Madrid"):
> ```cpp
> String city = "Madrid,ES";  // Especificar España
> ```

```
  Arduino IDE 2.x
  ┌────────────────────────────────────────────────────────┐
  │ [weather_forecast_led_matrix.ino] [arduino_secrets.h]  │ ← Pestañas
  │                                                        │
  │ 1  /*                                                  │
  │ 2   * Previsión Meteorológica en Matriz LED            │
  │ 3   * Arduino UNO Q                                    │
  │ 4   */                                                 │
  │                                                        │
  │ 5  String city = "Madrid";  // ← Ciudad configurada    │
  │                                                        │
  └────────────────────────────────────────────────────────┘
```

---

## Paso 7: Seleccionar la Placa y el Puerto

1. Ve a **Herramientas → Placa** y selecciona **"Arduino UNO Q"**
2. Ve a **Herramientas → Puerto** y selecciona el puerto de tu Arduino

```
  Herramientas
  ├── Placa: "Arduino UNO Q"                 ← Seleccionar
  ├── Puerto: "COM3 (Arduino UNO Q)"          ← Windows
  │         ó "/dev/tty.usbmodem14201"        ← macOS
  │         ó "/dev/ttyACM0 (Arduino UNO Q)"  ← Linux
  └── Gestor de Placas...
```

> 💡 Si el puerto no aparece, desconecta y vuelve a conectar el cable USB-C.

---

## Paso 8: Compilar y Subir el Sketch

```
  Barra de herramientas del IDE:

  [✓ Verificar]  [→ Subir]  [⎋ Parar]  [🔍 Monitor Serie]
       │               │
       │               └── Compila Y sube a la placa
       └────────────── Solo compila (para verificar errores)
```

1. Haz clic en **"Verificar"** (✓) — espera a que compile sin errores
2. Si no hay errores, haz clic en **"Subir"** (→)
3. Observa la barra de progreso y los mensajes:

```
  Panel de salida:
  ─────────────────────────────────────────────────────
  Compilando sketch...
  El sketch usa 98450 bytes (37%) del espacio de programa.
  Las variables globales usan 12345 bytes (23%) de memoria dinámica.
  ─────────────────────────────────────────────────────
  Subiendo...
  ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●  100%
  ─────────────────────────────────────────────────────
  avrdude: 98450 bytes of flash written
  ¡Carga completada!
  ─────────────────────────────────────────────────────
```

> ⚠️ Durante la carga los LEDs TX/RX parpadean rápidamente. **No desconectes el cable**.

---

## Paso 9: Verificar el Funcionamiento

### 9.1 Monitor Serie

1. Haz clic en el icono del **Monitor Serie** (🔍) o usa **Ctrl+Shift+M**
2. Configura la velocidad a **9600 baudios**
3. Deberías ver la siguiente salida:

```
  Monitor Serie  (9600 baudios)
  ─────────────────────────────────────────────────────────
  === Previsión Meteorológica en Matriz LED ===
  Placa: Arduino UNO Q
  Ciudad: Madrid

  Conectando a la red WiFi 'MiRedWiFi'...........
  ¡Conectado al WiFi!
  ----------------------------------------
  Dirección IP: 192.168.1.42
  Intensidad señal (RSSI): -58 dBm
  ----------------------------------------
  Obteniendo datos del tiempo para Madrid...
  Código de respuesta HTTP: 200
  === Datos Meteorológicos ===
  Ciudad: Madrid
  Condición: clear sky
  Temperatura: 18.3°C
  Humedad: 45%
  Viento: 3.2 m/s
  ============================
  Mostrando: ☀️ Despejado
  ─────────────────────────────────────────────────────────
```

### 9.2 Visualización en la Matriz LED

Según el tiempo en Madrid, la matriz LED mostrará uno de estos iconos:

```
  ☀️  DESPEJADO        🌤️  PARCIALMENTE         ⛅  NUBLADO
                           NUBLADO
  · · ● ● ● · ·        · · ● ● ● · ·          · ● ● ● ● · ·
  · ● · · · ● ·        · ● · · · ● ·          · ● · · · ● ·
  ● · · ● · · ●        ● · · ● · · ●          ● · · · · · ●
  ● · ● ● ● · ●        ● ● ● ● ● ● ●          · ● ● ● ● ● ·
  ● · · ● · · ●        · ● ● ● ● ● ·          · · ● ● ● · ·
  · ● · · · ● ·        · · · · · · ·          · · · · · · ·
  · · ● ● ● · ·        · · · · · · ·          · · · · · · ·

  🌧️  LLUVIA           🌩️  TORMENTA            🌨️  NIEVE

  · ● ● ● ● ● ·        · ● ● ● ● ● ·          · · · · · · ·
  ● · · · · · ●        ● · · · · · ●          · ● · ● · ● ·
  · ● ● ● ● ● ·        · ● ● ● ● ● ·          ● · ● · ● · ●
  · ↓ · ↓ · ↓ ·        · ● · ● · ● ·          · ● · ● · ● ·
  · · ↓ · ↓ · ·        · · ⚡· ⚡· ·          ● · ● · ● · ●
  · ↓ · ↓ · ↓ ·        · · · ↓ · · ·          · ● · ● · ● ·
  · · ↓ · ↓ · ·        · · · · · · ·          · · · · · · ·
```

---

## Solución de Problemas Comunes

| Problema | Posible causa | Solución |
|----------|---------------|----------|
| La placa no aparece en "Puerto" | Cable solo de carga | Usa un cable USB de datos |
| Error de compilación: biblioteca no encontrada | Biblioteca no instalada | Instala la biblioteca desde el Gestor de Bibliotecas |
| Error WiFi: módulo no encontrado | Selección incorrecta de placa | Verifica que sea "Arduino UNO Q" en Herramientas → Placa |
| Error HTTP 401 | API Key incorrecta | Verifica la clave en `arduino_secrets.h` |
| Error HTTP 404 | Ciudad no encontrada | Comprueba el nombre de la ciudad (prueba con "Madrid,ES") |
| Matriz LED no muestra nada | Falta de WiFi / datos | Revisa el Monitor Serie para ver el error |
| La clave API no funciona | Clave recién creada | Espera 2 horas y vuelve a intentarlo |

---

## Diagrama de Flujo del Programa

```
  ┌─────────────┐
  │   INICIO    │
  └──────┬──────┘
         │
         ▼
  ┌─────────────────────────────────┐
  │  setup()                        │
  │  - Inicializar Serial (9600)    │
  │  - Inicializar Matriz LED       │
  │  - Verificar módulo WiFi        │
  │  - Conectar al WiFi             │
  │  - Primera llamada a la API     │
  └─────────────────────────────────┘
         │
         ▼
  ┌─────────────────────────────────────────────────────┐
  │  loop()  (se repite indefinidamente)                │
  │                                                     │
  │  ¿Han pasado 10 minutos? ──── NO ──── esperar 100ms │
  │                │                                    │
  │               SÍ                                   │
  │                │                                    │
  │                ▼                                    │
  │  ¿Sigue conectado al WiFi?                          │
  │       NO → reconectar WiFi                          │
  │       SÍ ↓                                          │
  │                │                                    │
  │                ▼                                    │
  │  Petición HTTP GET a OpenWeatherMap                 │
  │  api.openweathermap.org/data/2.5/weather?q=Madrid   │
  │                │                                    │
  │                ▼                                    │
  │  Analizar JSON → extraer temperatura, condición...  │
  │                │                                    │
  │                ▼                                    │
  │  Seleccionar icono según código de condición        │
  │  2xx→Tormenta  5xx→Lluvia  6xx→Nieve  800→Sol       │
  │  3xx→Llovizna  7xx→Niebla  80x→Nubes               │
  │                │                                    │
  │                ▼                                    │
  │  Mostrar icono en Matriz LED                        │
  │  Imprimir datos en Monitor Serie                    │
  └─────────────────────────────────────────────────────┘
```

---

## 📁 Archivos del Proyecto

El ejemplo completo con todos los comentarios **traducidos al español** está en:

```
weather_forecast_led_matrix/
├── weather_forecast_led_matrix.ino   ← Sketch principal
└── arduino_secrets.h                 ← Credenciales (EDITAR ESTE ARCHIVO)
```

👉 [Ir a la carpeta del ejemplo](./weather_forecast_led_matrix/)

---

## 🔗 Referencias y Recursos

- [Arduino UNO Q — Página oficial de Arduino](https://store.arduino.cc)
- [Arduino App Lab](https://lab.arduino.cc)
- [Arduino IDE 2 — Descarga](https://www.arduino.cc/en/software)
- [OpenWeatherMap API — Documentación](https://openweathermap.org/current)
- [Registro gratuito en OpenWeatherMap](https://home.openweathermap.org/users/sign_up)
- [Documentación ArduinoJson](https://arduinojson.org)
- [Arduino LED Matrix Library](https://docs.arduino.cc/libraries/arduino_led_matrix/)
- [Referencia WiFiS3 Library](https://docs.arduino.cc/libraries/wifish3/)

---

## 📄 Licencia

MIT License — Ver archivo [LICENSE](LICENSE)

