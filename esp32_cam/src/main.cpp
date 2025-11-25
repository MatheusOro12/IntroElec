#include <esp_camera.h>
#include <WebServer.h>
#include <Arduino.h>
#include "wifi_config.h"
#include "camera_module.h"
#include "file_change.h"
#include "server.h"

void setup() {
    Serial.begin(115200);
    setupWiFi();
    setupCamera();
    setupStorage();
    setupTimelapse();
    setupServer();
}

void loop() {
    handleTimelapse();
    handleServer();
}