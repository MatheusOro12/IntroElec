#include "server.h"
#include <WebServer.h>
#include "sensors.h"
#include "control.h"

WebServer server(80);

void handleStatus() {
    float t = getTemperature();
    float h = getHumidity();
    String msg = String("Temp: ") + t + "C Hum: " + h + "%";
    server.send(200, "text/plain", msg);
}

void setupServer() {
    server.on("/status", handleStatus);
    server.begin();
}

void handleServer() {
    server.handleClient();
}