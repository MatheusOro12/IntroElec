#include <WebServer.h>
#include <esp_camera.h>
#include <Arduino.h>
#include "wifi_config.h"
#include "camera_module.h"
#include "file_change.h"
#include "server.h"

/*
muito longo e esquisito mas basicamente converte 
o tipo de arquivo do tipo padrão suportado pela 
camera para jpg que o html suporta
*/
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