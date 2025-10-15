#include "control.h"
#include <Arduino.h>
#include "sensors.h"

#define PELTIER_HEAT 25
#define PELTIER_COOL 26

// Valores configuráveis
float targetTemperature = 37.0;
float targetHumidity = 50.0;

void setupControl() {
    ledcSetup(0, 1000, 8);
    ledcSetup(1, 1000, 8);
    ledcAttachPin(PELTIER_HEAT, 0);
    ledcAttachPin(PELTIER_COOL, 1);
}

void updateControl() {
    float t = getTemperature();

    if (t < targetTemperature - 0.5) {
        ledcWrite(0, 200);
        ledcWrite(1, 0);
    } else if (t > targetTemperature + 0.5) {
        ledcWrite(0, 0);
        ledcWrite(1, 200);
    } else {
        ledcWrite(0, 0);
        ledcWrite(1, 0);
    }
}

// Getters e setters
float getTargetTemperature() { return targetTemperature; }
float getTargetHumidity() { return targetHumidity; }

void setTargetTemperature(float t) { targetTemperature = t; }
void setTargetHumidity(float h) { targetHumidity = h; }
