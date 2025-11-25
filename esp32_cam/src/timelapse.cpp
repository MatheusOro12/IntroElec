
#include "esp_camera.h"
#include "img_converters.h"
#include "FS.h"
#include "SD_MMC.h"

#include "timelapse.h"
#include "camera_module.h"
#include "storage.h"
#include "zip_utils.h"
#include <Arduino.h>

static unsigned long lastCapture = 0;
static const unsigned long interval = 3600000UL; // 1 hora
static int photoCount = 0;
static const int maxPhotos = 120; // 5 dias = 120h
static String zipPath = "/timelapse.zip";

void setupTimelapse() {
    setupStorage();   // SD
    lastCapture = millis();
}

void handleTimelapse() {

    unsigned long now = millis();

    if (photoCount >= maxPhotos) return;

    if (now - lastCapture >= interval) {

        lastCapture = now;
        photoCount++;

        // captura o frame YUV422
        camera_fb_t* fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Falha ao capturar imagem!");
            return;
        }

        // converte para JPG (80% qualidade)
        uint8_t* jpg = nullptr;
        size_t jpg_len = 0;

        if (!frame2jpg(fb, 80, &jpg, &jpg_len)) {
            Serial.println("Falha ao converter para JPG");
            esp_camera_fb_return(fb);
            return;
        }

        // salva no SD
        String filename = "/photo_" + String(photoCount) + ".jpg";
        File file = SD_MMC.open(filename, FILE_WRITE);

        if (!file) {
            Serial.println("Falha ao abrir arquivo no SD");
            free(jpg);
            esp_camera_fb_return(fb);
            return;
        }

        file.write(jpg, jpg_len);
        file.close();

        free(jpg);
        esp_camera_fb_return(fb);

        Serial.println("Foto salva: " + filename);

        // se terminou as fotos → gerar ZIP
        if (photoCount == maxPhotos) {
            Serial.println("Gerando ZIP...");
            zip_create("/timelapse.zip");
            Serial.println("ZIP gerado!");
        }
    }
}

const char* getZipPath() {
    return zipPath.c_str();
}
