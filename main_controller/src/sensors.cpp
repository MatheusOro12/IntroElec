#include "sensors.h"
#include <DHT.h>

#define DHT_PIN 4 //pino do sensor
#define DHTTYPE DHT11 //tipo do sensor

DHT dht(DHT_PIN, DHTTYPE); //cria o objeto do sensor DHT
float temperature = 0, humidity = 0; // inicia as variaveis com um valor generico

void setupSensors() {
    dht.begin(); //usa o metodo interno do DHT que inicia o sensor
}

void readSensors() {
    temperature = dht.readTemperature(); //usa metodo interno que retorna a temperatura
    humidity = dht.readHumidity(); //usa metodo interno que retorna umidade
}

float getTemperature() { return temperature; } //getter de temperatura
float getHumidity() { return humidity; } //getter de umidade