#include "sensors.h"
#include <DHT.h>

#define DHT_PIN 4 //pino do sensor
#define DHTTYPE DHT11 //tipo do sensor

DHT dht(DHT_PIN, DHTTYPE);
float temperature = 0, humidity = 0;

void setupSensors() {
    dht.begin();
}

void readSensors() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}

float getTemperature() { return temperature; } //getter de temperatura
float getHumidity() { return humidity; } //getter de umidade