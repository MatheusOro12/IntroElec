#include "wifi_config.h"
#include <WiFi.h>

const char* WIFI_SSID = "iPhone de Matheus"; //nome da rede wifi
const char* WIFI_PASS = "xenosauro1"; //senha da rede wifi

void setupWiFi() { //conecta no wifi
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());
}