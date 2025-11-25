#pragma once
#include <WebServer.h>

extern WebServer server;

WebServer server(80);

void setupServer();
void handleServer();