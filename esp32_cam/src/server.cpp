#include "server.h"
#include "timelapse.h"
#include <SD_MMC.h>
#include <esp_camera.h>

WebServer server(80);   // DEFINIÇÃO única (correto!)

void setupServer() {
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

void handleServer() {
    server.handleClient();
}

void handleJpg() {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
        server.send(500, "text/plain", "Erro ao capturar imagem");
        return;
    }

    uint8_t* jpg = nullptr;
    size_t jpg_len = 0;

    if (!frame2jpg(fb, 80, &jpg, &jpg_len)) {
        esp_camera_fb_return(fb);
        server.send(500, "text/plain", "Falha ao converter para JPG");
        return;
    }

    server.sendHeader("Content-Type", "image/jpeg");
    server.send_P(200, "image/jpeg", (char*)jpg, jpg_len);

    free(jpg);
    esp_camera_fb_return(fb);
}
