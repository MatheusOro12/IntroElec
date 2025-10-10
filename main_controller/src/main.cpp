#include <Arduino.h>
#include "wifi_config.h"
#include "server.h"
#include "sensors.h"
#include "control.h"
#include "lcd_display.h"

void setup() {
Serial.begin(115200);
setupWiFi();
setupServer();
setupSensors();
setupControl();
setupLCD();
}


void loop() {
readSensors();
updateControl();
updateLCD();
handleServer();
delay(1000);
}