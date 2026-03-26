/*
  Previsión Meteorológica en Matriz LED
  =====================================
  Este sketch conecta la placa Arduino UNO Q a internet mediante WiFi,
  obtiene los datos meteorológicos actuales de la ciudad de Madrid usando
  la API pública de OpenWeatherMap, y muestra el estado del tiempo en la
  matriz LED integrada de 12×8 LEDs.

  Basado en el ejemplo "Weather forecast on LED matrix" de Arduino App Lab.
  Adaptado y comentado en español para Arduino UNO Q.

  --- REQUISITOS DE HARDWARE ---
  - Placa Arduino UNO Q
  - Cable USB-C para programar y alimentar la placa
  - Red WiFi 2.4 GHz disponible cerca del dispositivo

  --- REQUISITOS DE SOFTWARE ---
  - Arduino IDE 2.x (descargar en https://www.arduino.cc/en/software)
  - Paquete de placa: "Arduino UNO Q Boards" (instalar desde Gestor de Placas)
  - Biblioteca: WiFiS3           (incluida con el paquete de la placa)
  - Biblioteca: ArduinoHttpClient (instalar desde Gestor de Bibliotecas)
  - Biblioteca: ArduinoJson v7.x  (instalar desde Gestor de Bibliotecas)
  - Biblioteca: Arduino_LED_Matrix (incluida con el paquete de la placa)

  --- CONFIGURACIÓN PREVIA ---
  1. Abre el archivo "arduino_secrets.h" (segunda pestaña del IDE)
  2. Reemplaza YOUR_WIFI_SSID con el nombre de tu red WiFi
  3. Reemplaza YOUR_WIFI_PASSWORD con la contraseña de tu red WiFi
  4. Regístrate gratis en https://openweathermap.org y copia tu API Key
  5. Reemplaza YOUR_OPENWEATHER_API_KEY con tu clave de la API

  --- NOTA SOBRE LA API KEY ---
  Las claves nuevas de OpenWeatherMap pueden tardar hasta 2 horas
  en activarse después del registro.

  Creado: Marzo 2025
  Versión: 1.0
  Licencia: Dominio público (CC0)
*/

// ════════════════════════════════════════════════════════════════
// SECCIÓN 1: INCLUSIÓN DE BIBLIOTECAS
// ════════════════════════════════════════════════════════════════

#include "arduino_secrets.h"    // Credenciales WiFi y API Key (archivo separado)
#include <WiFiS3.h>             // Conectividad WiFi para Arduino UNO Q
#include <ArduinoHttpClient.h>  // Realización de peticiones HTTP
#include <ArduinoJson.h>        // Análisis (parsing) de respuestas en formato JSON
#include "Arduino_LED_Matrix.h" // Control de la matriz LED integrada 12×8

// ════════════════════════════════════════════════════════════════
// SECCIÓN 2: CONFIGURACIÓN DE LA CIUDAD Y LA API
// ════════════════════════════════════════════════════════════════

/*
  Ciudad para la que se obtendrá la previsión meteorológica.
  Puedes cambiar "Madrid" por cualquier ciudad del mundo.
  Para evitar ambigüedades, usa el formato "Ciudad,CodigoPais"
  Ejemplos: "Barcelona,ES" / "Paris,FR" / "New York,US"
*/
String city = "Madrid,ES";

// Servidor de la API de OpenWeatherMap (sin HTTPS para compatibilidad básica)
const char weatherServer[] = "api.openweathermap.org";

// ════════════════════════════════════════════════════════════════
// SECCIÓN 3: CREDENCIALES WIFI (definidas en arduino_secrets.h)
// ════════════════════════════════════════════════════════════════

char ssid[] = SECRET_SSID;      // Nombre de la red WiFi (SSID)
char password[] = SECRET_PASS;  // Contraseña de la red WiFi

// Estado actual de la conexión WiFi (se actualiza automáticamente)
int estadoWifi = WL_IDLE_STATUS;

// ════════════════════════════════════════════════════════════════
// SECCIÓN 4: PATRONES GRÁFICOS PARA LA MATRIZ LED (12 col × 8 fil)
// ════════════════════════════════════════════════════════════════

/*
  La matriz LED integrada tiene 12 columnas y 8 filas (96 LEDs en total).
  Cada icono se define como un array de 3 valores uint32_t.
  Los 96 bits de datos se distribuyen así:
    - Primer  uint32_t: bits 95..64 (filas 1-3 aprox.)
    - Segundo uint32_t: bits 63..32 (filas 4-6 aprox.)
    - Tercer  uint32_t: bits 31..0  (filas 7-8 aprox.)
  Un bit en '1' enciende el LED; en '0' lo apaga.
*/

// Objeto para controlar la matriz LED integrada
ArduinoLEDMatrix matrizLED;

// --- Icono: SOL (condición 800 - cielo despejado) ---
// Representa un círculo brillante con rayos
const uint32_t iconoSol[3] = {
  0x000a2000,
  0x004e4e40,
  0x000a2000
};

// --- Icono: NUBES (condiciones 801-804 - parcial o totalmente nublado) ---
// Representa una nube compacta
const uint32_t iconoNublado[3] = {
  0x00060000,
  0x006f6f00,
  0x00000000
};

// --- Icono: LLUVIA (condiciones 300-531 - llovizna o lluvia) ---
// Representa una nube con gotas cayendo
const uint32_t iconoLluvia[3] = {
  0x00060000,
  0x006f6f00,
  0x00555500
};

// --- Icono: NIEVE (condiciones 600-622 - nieve o aguanieve) ---
// Representa copos de nieve cayendo
const uint32_t iconoNieve[3] = {
  0x00aa5500,
  0x00aa5500,
  0x00aa5500
};

// --- Icono: TORMENTA ELÉCTRICA (condiciones 200-232) ---
// Representa nubes con un rayo
const uint32_t iconoTormenta[3] = {
  0x00060000,
  0x007f3f00,
  0x00001800
};

// --- Icono: NIEBLA / CALIMA (condiciones 700-781) ---
// Representa líneas horizontales de niebla
const uint32_t iconoNiebla[3] = {
  0x00ff0000,
  0x007f0000,
  0x00ff0000
};

// --- Icono: CARGANDO (animación mientras se obtienen los datos) ---
// Tres puntos parpadeantes en el centro de la pantalla
const uint32_t iconoCargando[3] = {
  0x00000000,
  0x00240000,
  0x00000000
};

// --- Icono: ERROR (WiFi o API no disponible) ---
// Muestra una "X" en la pantalla
const uint32_t iconoError[3] = {
  0x00822000,
  0x00140000,
  0x00822000
};

// ════════════════════════════════════════════════════════════════
// SECCIÓN 5: VARIABLES DE TEMPORIZACIÓN
// ════════════════════════════════════════════════════════════════

/*
  Intervalo entre actualizaciones del tiempo: 10 minutos.
  La cuenta gratuita de OpenWeatherMap permite hasta 60 peticiones
  por minuto y 1.000.000 peticiones por mes, así que 10 minutos
  es un intervalo razonable y respetuoso con los límites de la API.

  Para pruebas puedes reducirlo temporalmente, por ejemplo a 60000 (1 min),
  pero recuerda volver a 600000 para el uso normal.
*/
const unsigned long INTERVALO_ACTUALIZACION_MS = 600000UL; // 10 minutos en ms

// Marca de tiempo de la última actualización exitosa (en milisegundos)
unsigned long tiempoUltimaActualizacion = 0;

// ════════════════════════════════════════════════════════════════
// SECCIÓN 6: OBJETOS DE RED
// ════════════════════════════════════════════════════════════════

// Cliente TCP/IP sobre WiFi (sin cifrado SSL para simplicidad)
WiFiClient clienteTCP;

// Cliente HTTP que usará el cliente TCP anterior
// Puerto 80 = HTTP estándar (sin cifrado)
HttpClient clienteHTTP(clienteTCP, weatherServer, 80);

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: setup()
// Se ejecuta UNA SOLA VEZ al arrancar o reiniciar la placa.
// Inicializa todos los subsistemas y realiza la primera consulta.
// ════════════════════════════════════════════════════════════════

void setup() {
  // --- Inicializar comunicación serie ---
  // Velocidad 9600 baudios = compatible con el Monitor Serie del IDE
  Serial.begin(9600);

  // Esperar hasta que el puerto serie esté listo
  // (necesario en placas con USB-CDC como el Arduino UNO Q)
  while (!Serial) {
    ; // Bucle vacío de espera
  }

  // --- Encabezado en el Monitor Serie ---
  Serial.println();
  Serial.println("╔══════════════════════════════════════════╗");
  Serial.println("║  Previsión Meteorológica en Matriz LED   ║");
  Serial.println("║  Arduino UNO Q                           ║");
  Serial.println("╚══════════════════════════════════════════╝");
  Serial.print("Ciudad configurada: ");
  Serial.println(city);
  Serial.println();

  // --- Inicializar la matriz LED ---
  matrizLED.begin();

  // Mostrar animación de "cargando" mientras nos conectamos
  matrizLED.loadFrame(iconoCargando);

  // --- Verificar que el módulo WiFi esté disponible ---
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR CRÍTICO: No se encontró el módulo WiFi.");
    Serial.println("Verifica que la placa seleccionada sea 'Arduino UNO Q'.");
    Serial.println("Programa detenido.");

    // Mostrar icono de error y detener la ejecución permanentemente
    matrizLED.loadFrame(iconoError);
    while (true) {
      // Bucle infinito: la placa se detiene aquí
    }
  }

  // --- Verificar versión del firmware WiFi ---
  String versionFirmwareActual = WiFi.firmwareVersion();
  if (versionFirmwareActual < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("AVISO: El firmware del módulo WiFi está desactualizado.");
    Serial.print("  Versión instalada:    ");
    Serial.println(versionFirmwareActual);
    Serial.print("  Versión recomendada:  ");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
    Serial.println("  Considera actualizar el firmware desde:");
    Serial.println("  Herramientas → Actualizar Firmware WiFi");
    Serial.println();
  }

  // --- Conectar a la red WiFi ---
  conectarAlWifi();

  // --- Primera consulta meteorológica ---
  actualizarDatosMeteorologicos();

  // Guardar el momento de la primera actualización
  tiempoUltimaActualizacion = millis();
}

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: loop()
// Se ejecuta REPETIDAMENTE en bucle después de setup().
// Solo actualiza los datos cuando ha pasado el intervalo definido.
// ════════════════════════════════════════════════════════════════

void loop() {
  // Calcular cuánto tiempo ha pasado desde la última actualización
  unsigned long tiempoTranscurrido = millis() - tiempoUltimaActualizacion;

  // ¿Ha llegado el momento de actualizar?
  if (tiempoTranscurrido >= INTERVALO_ACTUALIZACION_MS) {
    Serial.println();
    Serial.println(">>> Actualizando datos (intervalo de 10 minutos)...");

    // Comprobar si seguimos conectados al WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi desconectado. Intentando reconectar...");
      conectarAlWifi();
    }

    // Obtener nuevos datos del tiempo
    actualizarDatosMeteorologicos();

    // Actualizar la marca de tiempo para el siguiente ciclo
    tiempoUltimaActualizacion = millis();
  }

  // Pequeña pausa para no saturar el procesador en el bucle
  delay(100);
}

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: conectarAlWifi()
// Intenta conectarse a la red WiFi configurada en arduino_secrets.h
// Reintenta automáticamente cada 10 segundos hasta conseguirlo.
// ════════════════════════════════════════════════════════════════

void conectarAlWifi() {
  Serial.print("Conectando a la red WiFi '");
  Serial.print(ssid);
  Serial.print("'");

  // Reintentar hasta que la conexión sea exitosa
  while (estadoWifi != WL_CONNECTED) {
    estadoWifi = WiFi.begin(ssid, password);

    // Esperar 10 segundos antes del próximo intento
    // (el módulo WiFi necesita tiempo para negociar la conexión)
    for (int i = 0; i < 10; i++) {
      delay(1000);
      Serial.print(".");
    }
  }

  Serial.println();
  Serial.println("¡Conectado al WiFi correctamente!");
  Serial.println("─────────────────────────────────");

  // Mostrar información de la conexión establecida
  mostrarInformacionWifi();
}

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: mostrarInformacionWifi()
// Imprime en el Monitor Serie los datos de la conexión WiFi activa.
// ════════════════════════════════════════════════════════════════

void mostrarInformacionWifi() {
  // Dirección IP asignada por el router (DHCP)
  IPAddress direccionIP = WiFi.localIP();
  Serial.print("Dirección IP asignada: ");
  Serial.println(direccionIP);

  // SSID de la red a la que estamos conectados
  Serial.print("Red WiFi (SSID):       ");
  Serial.println(WiFi.SSID());

  // Intensidad de la señal (RSSI): cuanto más cerca de 0 dBm, mejor señal
  // Buena señal: por encima de -70 dBm
  // Señal débil:  por debajo de -80 dBm
  long rssi = WiFi.RSSI();
  Serial.print("Intensidad señal WiFi: ");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.println("─────────────────────────────────");
}

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: actualizarDatosMeteorologicos()
// Construye la URL de la petición, llama a la API de OpenWeatherMap,
// analiza la respuesta JSON y actualiza la matriz LED con el icono
// apropiado para las condiciones meteorológicas actuales.
// ════════════════════════════════════════════════════════════════

void actualizarDatosMeteorologicos() {
  // Mostrar icono de "cargando" mientras se obtienen los datos
  matrizLED.loadFrame(iconoCargando);

  Serial.print("Consultando la API para '");
  Serial.print(city);
  Serial.println("'...");

  // Construir la URL del endpoint de la API
  // Parámetros:
  //   q=          : Nombre de la ciudad (y código de país opcional)
  //   units=metric: Temperatura en grados Celsius (vs. Fahrenheit con imperial)
  //   appid=      : Tu clave de API personal
  String urlEndpoint = "/data/2.5/weather?q=" + city +
                       "&units=metric&appid=" + String(SECRET_API_KEY);

  // Realizar la petición HTTP GET
  clienteHTTP.get(urlEndpoint);

  // Leer el código de estado de la respuesta HTTP
  // 200 = OK (éxito)
  // 401 = No autorizado (API Key incorrecta)
  // 404 = No encontrado (ciudad no encontrada)
  // 429 = Demasiadas peticiones (límite de la API superado)
  int codigoEstado = clienteHTTP.responseStatusCode();

  Serial.print("Respuesta HTTP: ");
  Serial.println(codigoEstado);

  if (codigoEstado == 200) {
    // --- Petición exitosa: leer y analizar el JSON ---
    String cuerpoRespuesta = clienteHTTP.responseBody();

    // Crear un documento JSON con capacidad suficiente para la respuesta
    // (la respuesta de la API básica ocupa aproximadamente 500 bytes)
    JsonDocument documentoJson;

    // Analizar (deserializar) la cadena JSON
    DeserializationError errorJson = deserializeJson(documentoJson, cuerpoRespuesta);

    if (errorJson) {
      // Error al analizar el JSON (respuesta malformada o truncada)
      Serial.print("ERROR al analizar el JSON: ");
      Serial.println(errorJson.c_str());
      matrizLED.loadFrame(iconoError);
      clienteHTTP.stop();
      return;
    }

    // --- Extraer los campos que necesitamos del JSON ---

    // Código numérico de la condición meteorológica
    // Referencia completa: https://openweathermap.org/weather-conditions
    int codigoCondicion = documentoJson["weather"][0]["id"];

    // Descripción corta en inglés (ej: "clear sky", "broken clouds")
    const char* descripcion = documentoJson["weather"][0]["description"];

    // Temperatura actual en Celsius (gracias a units=metric)
    float temperatura = documentoJson["main"]["temp"];

    // Temperatura sensación térmica en Celsius
    float sensacionTermica = documentoJson["main"]["feels_like"];

    // Humedad relativa del aire en porcentaje (0-100%)
    int humedad = documentoJson["main"]["humidity"];

    // Velocidad del viento en metros por segundo
    float velocidadViento = documentoJson["wind"]["speed"];

    // Nombre de la ciudad confirmado por la API (puede diferir ligeramente)
    const char* nombreCiudad = documentoJson["name"];

    // Código del país (ej: "ES" para España)
    const char* codigoPais = documentoJson["sys"]["country"];

    // Visibilidad en metros (campo opcional, puede no estar siempre presente)
    int visibilidad = documentoJson["visibility"] | 0;

    // --- Imprimir los datos en el Monitor Serie ---
    Serial.println();
    Serial.println("╔══════════════════════════════════╗");
    Serial.println("║     DATOS METEOROLÓGICOS         ║");
    Serial.println("╠══════════════════════════════════╣");
    Serial.print("║ Ciudad:          ");
    Serial.print(nombreCiudad);
    Serial.print(", ");
    Serial.println(codigoPais);
    Serial.print("║ Condición:       ");
    Serial.println(descripcion);
    Serial.print("║ Temperatura:     ");
    Serial.print(temperatura, 1);
    Serial.println(" °C");
    Serial.print("║ Sensación:       ");
    Serial.print(sensacionTermica, 1);
    Serial.println(" °C");
    Serial.print("║ Humedad:         ");
    Serial.print(humedad);
    Serial.println(" %");
    Serial.print("║ Viento:          ");
    Serial.print(velocidadViento, 1);
    Serial.println(" m/s");
    if (visibilidad > 0) {
      Serial.print("║ Visibilidad:     ");
      Serial.print(visibilidad / 1000.0, 1);
      Serial.println(" km");
    }
    Serial.print("║ Código condición: ");
    Serial.println(codigoCondicion);
    Serial.println("╚══════════════════════════════════╝");

    // --- Actualizar la matriz LED con el icono correspondiente ---
    seleccionarYMostrarIcono(codigoCondicion);

  } else if (codigoEstado == 401) {
    // API Key no válida o no activada aún
    Serial.println("ERROR 401: API Key incorrecta o no activada.");
    Serial.println("Verifica la clave en arduino_secrets.h.");
    Serial.println("Recuerda que las claves nuevas tardan hasta 2 horas en activarse.");
    matrizLED.loadFrame(iconoError);

  } else if (codigoEstado == 404) {
    // Ciudad no encontrada en la base de datos
    Serial.println("ERROR 404: Ciudad no encontrada.");
    Serial.print("Verifica el nombre de la ciudad: '");
    Serial.print(city);
    Serial.println("'");
    Serial.println("Prueba con el formato 'Ciudad,CodigoPais' (ej: 'Madrid,ES').");
    matrizLED.loadFrame(iconoError);

  } else {
    // Otro error HTTP inesperado
    Serial.print("ERROR HTTP inesperado. Código: ");
    Serial.println(codigoEstado);
    matrizLED.loadFrame(iconoError);
  }

  // Cerrar la conexión HTTP para liberar recursos de memoria
  clienteHTTP.stop();
}

// ════════════════════════════════════════════════════════════════
// FUNCIÓN: seleccionarYMostrarIcono(int codigoCondicion)
// Elige el icono de la matriz LED según el código de condición
// meteorológica devuelto por la API de OpenWeatherMap.
//
// Tabla de códigos de condición (resumida):
//   2xx (200-232): Tormenta eléctrica
//   3xx (300-321): Llovizna (drizzle)
//   5xx (500-531): Lluvia
//   6xx (600-622): Nieve o aguanieve
//   7xx (700-781): Fenómenos atmosféricos (niebla, calima, tornado...)
//   800:           Cielo despejado
//   80x (801-804): Nubes (parciales a totales)
//
// Referencia completa:
//   https://openweathermap.org/weather-conditions
// ════════════════════════════════════════════════════════════════

void seleccionarYMostrarIcono(int codigoCondicion) {

  if (codigoCondicion >= 200 && codigoCondicion < 300) {
    // Grupo 2xx: Tormenta eléctrica con lluvia o nieve
    Serial.println("Icono: ⚡ TORMENTA ELÉCTRICA");
    matrizLED.loadFrame(iconoTormenta);

  } else if (codigoCondicion >= 300 && codigoCondicion < 400) {
    // Grupo 3xx: Llovizna ligera (drizzle)
    Serial.println("Icono: 🌦️ LLOVIZNA");
    matrizLED.loadFrame(iconoLluvia);

  } else if (codigoCondicion >= 500 && codigoCondicion < 600) {
    // Grupo 5xx: Lluvia (de ligera a muy intensa)
    Serial.println("Icono: 🌧️ LLUVIA");
    matrizLED.loadFrame(iconoLluvia);

  } else if (codigoCondicion >= 600 && codigoCondicion < 700) {
    // Grupo 6xx: Nieve, aguanieve o granizo
    Serial.println("Icono: 🌨️ NIEVE / AGUANIEVE");
    matrizLED.loadFrame(iconoNieve);

  } else if (codigoCondicion >= 700 && codigoCondicion < 800) {
    // Grupo 7xx: Fenómenos atmosféricos variados
    // 701 = niebla, 711 = humo, 721 = calima, 731 = polvo,
    // 741 = niebla densa, 751 = arena, 761 = polvo, 771 = ráfagas, 781 = tornado
    Serial.println("Icono: 🌫️ NIEBLA / ATMÓSFERA");
    matrizLED.loadFrame(iconoNiebla);

  } else if (codigoCondicion == 800) {
    // 800 exactamente: cielo completamente despejado
    Serial.println("Icono: ☀️ DESPEJADO");
    matrizLED.loadFrame(iconoSol);

  } else if (codigoCondicion > 800 && codigoCondicion < 900) {
    // Grupo 80x: Nubes en distintos grados
    // 801 = pocas nubes (11-25%), 802 = nubes dispersas (25-50%)
    // 803 = nubes rotas (51-84%), 804 = cielo cubierto (85-100%)
    Serial.println("Icono: ⛅ NUBLADO");
    matrizLED.loadFrame(iconoNublado);

  } else {
    // Código desconocido o fuera de rango
    Serial.print("Código de condición no reconocido: ");
    Serial.println(codigoCondicion);
    Serial.println("Icono: ❓ DESCONOCIDO (mostrando animación de carga)");
    matrizLED.loadFrame(iconoCargando);
  }
}
