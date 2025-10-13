#include "storage.h"
#include <SD_MMC.h>
#include <esp_camera.h>
#include <FS.h>


void setupStorage() {
if (!SD_MMC.begin()) {
Serial.println("Card Mount Failed");
}
}


void captureAndSavePhoto() {
camera_fb_t* fb = esp_camera_fb_get();
if (!fb) {
Serial.println("Camera capture failed");
return;
}
String path = "/photo_" + String(millis()) + ".jpg";
File file = SD_MMC.open(path, FILE_WRITE);
if (!file) {
Serial.println("Failed to open file");
return;
}
file.write(fb->buf, fb->len);
file.close();
esp_camera_fb_return(fb);
Serial.println("Photo saved: " + path);
}