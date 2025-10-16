#include <Arduino.h>
#include "wifi_config.h"
#include "server.h"
#include "sensors.h"
#include "control.h"
#include "lcd_display.h"
#include "mdns_config.h"

void setup() {
    Serial.begin(115200);
    setupWiFi();
    setupMDNS();
    setupSensors();
    setupControl();
    setupLCD();
    setupServer();

}


void loop() {
//readSensors();
//updateControl();
updateLCD();
//handleServer();
delay(100);
}