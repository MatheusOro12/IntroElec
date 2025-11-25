#include "server.h"
#include "timelapse.h"
#include <SD_MMC.h>
#include <esp_camera.h>

void setupServer(){ //incia o servidor
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
    });// codigo html do server
    server.on("/jpg", handleJpg);

    server.on("/download", []() {
        File zipFile = SD_MMC.open("/timelapse.zip");
        if (!zipFile) {
            server.send(500, "text/plain", "ZIP não encontrado");
            return;
        }
        server.streamFile(zipFile, "application/zip");
        zipFile.close();
    });

    server.begin();
    Serial.println("Servidor iniciado!");
}

void handleServer(){
    server.handleClient();
}