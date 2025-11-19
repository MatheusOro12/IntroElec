#include "camera_module.h"
#include <esp_camera.h>
#include <Arduino.h>

//FIXME: maybe change the path to the foto taken 
void setupCamera() { //inica a camera com as portas definidas ligadas na esp32
    camera_config_t config; //cria o objeto de configuracao da camera
    config.ledc_channel = LEDC_CHANNEL_0; //define a porta conectada na LED imbutida
    config.ledc_timer   = LEDC_TIMER_0;
    config.pin_d0       = 5; //<-|
    config.pin_d1       = 18;//  |
    config.pin_d2       = 19;//  |
    config.pin_d3       = 21;//  |
    config.pin_d4       = 36;//  |
    config.pin_d5       = 39;//  |
    config.pin_d6       = 34;//  |
    config.pin_d7       = 35;//  |
    config.pin_xclk     = 0; //  |--tudo isso eh porta da camera
    config.pin_pclk     = 22;//  |
    config.pin_vsync    = 25;//  |
    config.pin_href     = 23;//  |
    config.pin_sccb_sda = 26;//  |
    config.pin_sccb_scl = 27;//  |
    config.pin_pwdn     = 32;//  |
    config.pin_reset    = -1;//<-/

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_YUV422; //tipo do arquivo a ser gerado pela camera
    config.frame_size   = FRAMESIZE_QVGA; 
    config.fb_count     = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) { //debug de erro caso ocorra
        Serial.printf("Erro ao iniciar a câmera: 0x%x\n", err);
    } else {
        Serial.println("Câmera iniciada com sucesso!");
    }
}
