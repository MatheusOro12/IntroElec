#include "control.h"
#include <Arduino.h>
#include "sensors.h"

#define PELTIER_HEAT 25 //porta que a peltier quente esta ligada
#define PELTIER_COOL 26 //porta que a peltier fria esta ligada

// Valores configuráveis
float targetTemperature = 37.0;
float targetHumidity = 30.0;

void setupControl() { //inicia o controle das peltier
    ledcSetup(0, 1000, 8);
    ledcSetup(1, 1000, 8);
    ledcAttachPin(PELTIER_HEAT, 0);
    ledcAttachPin(PELTIER_COOL, 1);
}

void updateControl() {
    float t = getTemperature();

    if (t < targetTemperature - 0.5) {// temp a baixo, liga aquecer
        ledcWrite(0, 200);
        ledcWrite(1, 0);
    } else if (t > targetTemperature + 0.5) { // temp a cima, liga resfriador
        ledcWrite(0, 0);
        ledcWrite(1, 200);
    } else {
        ledcWrite(0, 0);
        ledcWrite(1, 0);
    }
}

// Getters: retorna a variavel
float getTargetTemperature() { return targetTemperature; }
float getTargetHumidity() { return targetHumidity; }

//setters: muda o valor da variavel
void setTargetTemperature(float t) { targetTemperature = t; }
void setTargetHumidity(float h) { targetHumidity = h; }
