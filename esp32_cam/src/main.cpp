#include <esp_camera.h>
#include <WebServer.h>
#include <Arduino.h>
#include "wifi_config.h"
#include "camera_module.h"

WebServer server(80);

void handleJpg() {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        server.send(500, "text/plain", "Falha ao capturar imagem");
        return;
    }

    uint8_t * jpg_buf = nullptr;
    size_t jpg_len = 0;

    if (fb->format != PIXFORMAT_JPEG) {

        if (!frame2jpg(fb, 80, &jpg_buf, &jpg_len)) {
            esp_camera_fb_return(fb);
            server.send(500, "text/plain", "Erro ao converter para JPEG");
            return;
        }

    } else {
        jpg_buf = fb->buf;
        jpg_len = fb->len;
    }


    server.sendHeader("Content-Type", "image/jpeg");
    server.sendHeader("Content-Disposition", "inline; filename=capture.jpg");
    server.sendContent((const char*)jpg_buf, jpg_len); 

    if (fb->format != PIXFORMAT_JPEG) {
        free(jpg_buf);
    }
    esp_camera_fb_return(fb);
}

void setup() {
    Serial.begin(115200);
    setupWiFi();
    setupCamera();

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

void loop() {
    server.handleClient();
}
