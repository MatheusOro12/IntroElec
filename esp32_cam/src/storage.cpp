#include "storage.h"
#include <SD_MMC.h>
#include <Arduino.h>

void setupStorage() {
    if (!SD_MMC.begin("/sdcard", true)) {
        Serial.println("Falha ao iniciar SD_MMC!");
    } else {
        Serial.println("SD_MMC iniciado!");
    }
}
