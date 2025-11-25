#include "wifi_config.h"
#include <WiFi.h>

const char* WIFI_SSID = "iPhone de Matheus"; //nome da rede wifi
const char* WIFI_PASS = "xenosauro1"; //senha da rede wifi

void setupWiFi() { //conecta no wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Conectando ao WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }

    Serial.println("\nWiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp32cam")) {
        Serial.println("mDNS ativo: http://esp32cam.local");
    } else {
        Serial.println("ERRO no mDNS");
    }
}