#include "camera_module.h"
#include <esp_camera.h>
#include <Arduino.h>

void setupCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;
    config.pin_d0       = 5;
    config.pin_d1       = 18;
    config.pin_d2       = 19;
    config.pin_d3       = 21;
    config.pin_d4       = 36;
    config.pin_d5       = 39;
    config.pin_d6       = 34;
    config.pin_d7       = 35;
    config.pin_xclk     = 0;
    config.pin_pclk     = 22;
    config.pin_vsync    = 25;
    config.pin_href     = 23;
    config.pin_sccb_sda = 26;
    config.pin_sccb_scl = 27;
    config.pin_pwdn     = 32;
    config.pin_reset    = -1;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_YUV422;
    config.frame_size   = FRAMESIZE_QVGA;
    config.fb_count     = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Erro ao iniciar a câmera: 0x%x\n", err);
    } else {
        Serial.println("Câmera iniciada com sucesso!");
    }
}
