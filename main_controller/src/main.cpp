#include <Arduino.h>
#include "wifi_config.h"
#include "server.h"
#include "sensors.h"
#include "control.h"
#include "lcd_display.h"
#include "mdns_config.h"

void setup() {
    Serial.begin(115200);
    setupWiFi(); //inicia o conexao wifi
    setupMDNS(); //configura o endereco do site
    setupSensors(); //inicia o sensor de temp/umid
    setupControl(); //inicia as peltier
    setupLCD(); //inicia a tela LCD
    setupServer(); //incia o server com o leyout do site

}


void loop() {
readSensors(); //leitura dos sensores
updateControl(); //atualiza os controles
updateLCD(); //atualiza os valores mostrados na tela
handleServer(); //altera os valores obtidos pelo site
delay(100);
}