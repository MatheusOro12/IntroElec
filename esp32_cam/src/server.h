#pragma once

#include <WebServer.h>
#include <esp_camera.h>
#include <Arduino.h>
#include "wifi_config.h"

WebServer server(80);

void setupServer();
void handleServer();