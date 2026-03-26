/*
  arduino_secrets.h
  ==================
  Archivo de configuración para credenciales sensibles del proyecto
  "Previsión Meteorológica en Matriz LED" para Arduino UNO Q.

  ╔══════════════════════════════════════════════════════════════╗
  ║  ⚠️  ATENCIÓN: SEGURIDAD DE CREDENCIALES                     ║
  ║                                                              ║
  ║  Este archivo contiene información confidencial:             ║
  ║  - Nombre y contraseña de tu red WiFi                        ║
  ║  - Tu clave personal de la API OpenWeatherMap                ║
  ║                                                              ║
  ║  NUNCA subas este archivo con datos reales a un              ║
  ║  repositorio público (GitHub, GitLab, etc.).                 ║
  ║  Está incluido en .gitignore para protegerte,                ║
  ║  pero verifica que no aparezca en tus commits.               ║
  ╚══════════════════════════════════════════════════════════════╝

  ─── INSTRUCCIONES DE CONFIGURACIÓN ──────────────────────────

  PASO 1: Configura tu red WiFi
  ─────────────────────────────
  Reemplaza "YOUR_WIFI_SSID" con el nombre exacto de tu red WiFi.
  El nombre es sensible a mayúsculas y minúsculas.
  Ejemplo: "MiCasaWiFi" o "Vodafone-5G-Salon"

  PASO 2: Configura la contraseña WiFi
  ─────────────────────────────────────
  Reemplaza "YOUR_WIFI_PASSWORD" con la contraseña de tu red WiFi.
  La encontrarás en la parte trasera de tu router o en la
  configuración de red de tu ordenador.

  PASO 3: Obtén y configura tu API Key de OpenWeatherMap
  ───────────────────────────────────────────────────────
  1. Ve a https://home.openweathermap.org/users/sign_up
  2. Crea una cuenta gratuita (no requiere tarjeta de crédito)
  3. Confirma tu correo electrónico
  4. Ve a "My API keys" en tu perfil
  5. Copia la clave predeterminada (una cadena de ~32 caracteres)
  6. Reemplaza "YOUR_OPENWEATHER_API_KEY" con esa clave

  ⏰ NOTA: Las claves nuevas pueden tardar hasta 2 horas en activarse.

  ─── PLAN GRATUITO DE OPENWEATHERMAP ────────────────────────
  El plan gratuito (Free) incluye:
    • 60 llamadas por minuto
    • 1.000.000 llamadas por mes
  Esto es más que suficiente para este proyecto (1 llamada / 10 min).
*/

// ─── CREDENCIALES WIFI ────────────────────────────────────────

// Nombre de la red WiFi (SSID) — sensible a mayúsculas
#define SECRET_SSID "YOUR_WIFI_SSID"

// Contraseña de la red WiFi
#define SECRET_PASS "YOUR_WIFI_PASSWORD"

// ─── CLAVE DE API DE OPENWEATHERMAP ──────────────────────────

// Clave de API personal de OpenWeatherMap
// Obtén la tuya gratis en: https://home.openweathermap.org/api_keys
#define SECRET_API_KEY "YOUR_OPENWEATHER_API_KEY"
