#include <Arduino.h>
#include "camera_module.h"
#include "storage.h"
#include "wifi_config.h"


unsigned long lastCapture = 0;


void setup() {
    Serial.begin(115200);
    setupWiFi();
    setupCamera();
    setupStorage();
}


void loop() {
    if (millis() - lastCapture > 3600000) {
        captureAndSavePhoto();
        lastCapture = millis();
    }
}