#pragma once

// Inicializa timers, SD e pastas da timelapse
void setupTimelapse();

// Deve ser chamado no loop() – dispara fotos na hora certa
void handleTimelapse();

// Opcional: retorna o caminho do último ZIP gerado
const char* getZipPath();
