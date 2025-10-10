// Required libraries: "esp_camera.h", "FS.h", "SD_MMC.h", "WiFi.h". Use Arduino core for ESP32 with camera support.

#include "esp_camera.h"
#include <WiFi.h>
#include "FS.h"
#include "SD_MMC.h"
#include <WebServer.h>
#include <SPI.h>
#include <time.h>
#include <Arduino.h>

const char* CAM_SSID = "YOUR_SSID"; // change
const char* CAM_PASSWORD = "YOUR_PASSWORD"; // change

WebServer camServer(80);

// Replace with your camera module pins (AI-Thinker typical)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5

#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// NTP settings
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3 * 3600;
const int   daylightOffset_sec = 0;

// takePicture() and save to SD
String getTimestamp() {
  time_t now;
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  char buf[32];
  strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &timeinfo);
  return String(buf);
}

bool initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  // init with high framesize for stills
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    return false;
  }
  return true;
}

bool initSD() {
  if(!SD_MMC.begin()) {
    Serial.println("SD Card Mount Failed");
    return false;
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return false;
  }
  Serial.println("SD initialized");
  return true;
}

String captureAndSave() {
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    return String();
  }

  String ts = getTimestamp();
  String path = "/photos/" + ts + ".jpg";

  File file = SD_MMC.open(path.c_str(), FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file in SD card");
    esp_camera_fb_return(fb);
    return String();
  }
  file.write(fb->buf, fb->len);
  file.close();
  esp_camera_fb_return(fb);
  Serial.print("Saved: "); Serial.println(path);
  return path;
}

void handleRootCam(){
  String html = "<h1>ESP32-CAM</h1>";
  html += "<p><a href=\"/capture\">Take photo now</a></p>";
  html += "<p><a href=\"/list\">List photos</a></p>";
  camServer.send(200, "text/html", html);
}

void handleCapture(){
  String p = captureAndSave();
  if (p.length()) camServer.send(200, "text/plain", "Saved: " + p);
  else camServer.send(500, "text/plain", "Failed capture");
}

String listPhotos() {
  String out = "<h2>Photos</h2><ul>";
  File root = SD_MMC.open("/photos");
  if(!root){
    return "No photos folder";
  }
  File file = root.openNextFile();
  while(file){
    String name = String(file.name());
    out += "<li><a href=\"/photo?f=" + name + "\">" + name + "</a></li>";
    file = root.openNextFile();
  }
  out += "</ul>";
  return out;
}

void handleList(){
  String html = listPhotos();
  camServer.send(200, "text/html", html);
}

void handlePhoto(){
  if (!camServer.hasArg("f")) { camServer.send(400, "text/plain", "missing f arg"); return; }
  String fname = camServer.arg("f");
  File file = SD_MMC.open(fname.c_str());
  if(!file){ camServer.send(404, "text/plain", "not found"); return; }
  camServer.streamFile(file, "image/jpeg");
  file.close();
}

void setupCam() {
  Serial.begin(115200);
  delay(1000);
  if (!initCamera()) {
    Serial.println("Camera init failed");
    return;
  }
  if (!initSD()) {
    Serial.println("SD init failed");
    return;
  }

  // Ensure photos directory exists
  SD_MMC.mkdir("/photos");

  WiFi.begin(CAM_SSID, CAM_PASSWORD);
  Serial.print("Connecting to WiFi");
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 20) {
    delay(500);
    Serial.print('.'); tries++;
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Camera IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi failed");
  }

  // setup NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
  }

  // Web handlers
  camServer.on("/", handleRootCam);
  camServer.on("/capture", handleCapture);
  camServer.on("/list", handleList);
  camServer.on("/photo", handlePhoto);
  camServer.begin();
}

// We'll take hourly pictures. Use millis() counter to trigger (not exact on sleep).
unsigned long lastCapture = 0;
const unsigned long HOUR_MS = 60UL * 60UL * 1000UL;

void loopCam(){
  camServer.handleClient();
  unsigned long now = millis();
  if (now - lastCapture >= HOUR_MS || lastCapture==0) {
    // take a picture and save
    String p = captureAndSave();
    lastCapture = now;
    Serial.println("Auto-captured: " + p);
  }
}