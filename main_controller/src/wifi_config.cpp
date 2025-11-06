#include "wifi_config.h"
#include <WiFi.h>

const char* WIFI_SSID = "iPhone de Matheus";
const char* WIFI_PASS = "xenosauro1";
 
void setupWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());
}