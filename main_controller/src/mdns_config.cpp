#include "mdns_config.h"
#include <ESPmDNS.h>
#include <Arduino.h>

const char* MDNS_NAME = "incubadora"; // O nome principal
//acessa em http://incubadora.local

void setupMDNS() {
    if (MDNS.begin(MDNS_NAME)) { //verifica se deu pra iniciar o servidor local
        Serial.println("mDNS iniciado!");
        Serial.printf("Acesse o controle em http://%s.local\n", MDNS_NAME);
    } else {
        Serial.println("Erro ao iniciar o mDNS.");
    }
}