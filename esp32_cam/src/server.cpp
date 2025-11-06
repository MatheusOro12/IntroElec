#include "server.h"
#include "file_change.h"


void setupServer(){
    server.on("/", []() {
        server.sendHeader("Content-Type", "text/html; charset=utf-8");
        server.send(200, "text/html",
            "<!DOCTYPE html>"
            "<html lang='pt-br'>"
            "<head>"
            "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
            "<title>ESP32 Camera</title>"
            "<style>"
            "body { text-align:center; font-family: sans-serif; margin:0; padding:0; }"
            "h1 { margin: 10px 0; }"
            "img { max-width:100%; max-height:80vh; display:block; margin:0 auto; }"
            "</style>"
            "</head>"
            "<body>"
            "<h1>Visualização da Câmera</h1>"
            "<img src='/jpg'>"
            "</body>"
            "</html>"
        );
    });
    server.on("/jpg", handleJpg);
    server.begin();
    Serial.println("Servidor iniciado!");
}

void handleServer(){
    server.handleClient();
}