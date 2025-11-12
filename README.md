<h1 align="center">🧪 Projeto de Introdução à Engenharia Elétrica</h1>

<p align="center">
  <b>Incubadora inteligente controlada por ESP32</b> <br>
  Projeto desenvolvido para a disciplina de Introdução à Engenharia Elétrica 2025
</p>


<!-- TOC -->

## Índice

- [🎈 Introdução](#-introdução)
- [⚙️ Hardware](#️-hardware)
  - [🤖 Controlador ESP32](#-controlador-principal-esp32)
  - [📷 Módulo ESP32-CAM](#-módulo-esp32-cam)
- [🖥️ Setup do Ambiente de Desenvolvimento](#️-setup-do-ambiente-de-desenvolvimento)
  - [🆔 Usando a IDE do Arduino](#-usando-a-ide-do-arduino)
  - [💻 Usando o VS Code com PlatformIO](#-usando-o-vs-code-com-platformio)
- [🖱️ Executando o Projeto](#️-executando-o-projeto)
  - [:keyboard: Operação do Controlador Principal](#️-operação-do-controlador-principal)
  - [:camera_flash: Operação do Módulo de Câmera](#-operação-do-módulo-de-câmera)
  - [:movie_camera: Gerando o Timelapse com Python](#-gerando-o-timelapse-com-python)
- [:adhesive_bandage: Solução de Problemas (Troubleshooting)](#-solução-de-problemas-troubleshooting)
- [📄 Licença](#-licença)

<!-- TOC -->

## 🎈 Introdução

Projeto de encubadora para a materia de introdução a engenharia eletrica, utilizando uma esp32 wroom, uma esp32-CAM, un sensor de temperatura e umidade DHT11.Este projeto consiste em uma **incubadora automatizada**, desenvolvida como parte da disciplina de **Introdução à Engenharia Elétrica**.  
O sistema utiliza uma **ESP32 WROOM** como controlador principal, uma **ESP32-CAM** para registro visual, e um **sensor DHT11** para monitoramento de **temperatura** e **umidade**.

O objetivo é **controlar e monitorar as condições ambientais internas**, além de **gerar um timelapse** das imagens capturadas ao longo do tempo.

## ⚙️ Hardware

### 🤖 Controlador principal esp32

- Microcontrolador: **ESP32-WROOM**
- Responsável pelo controle da incubadora:
  - Leitura do sensor de temperatura e umidade (**DHT11**)
  - Controle de aquecimento e ventilação (via **GPIOs**)
  - Comunicação com a **ESP32-CAM** via rede Wi-Fi
  - Envio dos dados para monitoramento

![esp32 pinout](/media/esp32_pin.jpg)

### 📷 Módulo esp32-CAM

- Módulo com câmera OV2640
- Responsável por capturar imagens periodicamente
- As imagens são armazenadas localmente ou enviadas via servidor HTTP
- Posteriormente, são usadas para gerar um **timelapse** com script Python

## 🖥️ Setup do Ambiente de Desenvolvimento

### 🆔 Usando a IDE do Arduino

1. Instale a [IDE do Arduino](https://www.arduino.cc/en/software)
2. No menu **Preferências**, adicione a URL: https://dl.espressif.com/dl/package_esp32_index.json
3. Vá em **Ferramentas → Placa → Gerenciador de Placas**, e instale **esp32 by Espressif Systems**
4. Selecione a placa:
   - Para o controlador: `ESP32 Dev Module`
   - Para a câmera: `AI Thinker ESP32-CAM`

5. Faça upload dos códigos correspondentes de cada módulo.

### 💻 Usando o VS Code com PlatformIO

1. Instale o [VS Code](https://code.visualstudio.com/)
2. Adicione a extensão **PlatformIO IDE**
3. Crie um novo projeto e selecione:
   - Board: `esp32dev` (para o controlador principal)
4. Copie os arquivos `.cpp` e `.h` do projeto para a pasta `src/`
5. Compile e envie para o dispositivo usando o botão “Upload”

## 🖱️ Executando o Projeto

### :keyboard: Operação do Controlador Principal

- O controlador inicializa a rede Wi-Fi e os sensores conectados  
- Lê a temperatura e umidade via DHT11  
- Atualiza o display LCD (quando conectado)  
- Se comunica com o módulo de câmera para sincronização

### :camera_flash: Operação do Módulo de Câmera

- Inicializa o servidor HTTP interno  
- Captura imagens em intervalos definidos  
- Permite acessar o feed via IP local (ex: `http://192.168.x.x`)  
- As imagens são armazenadas em `/data/` ou `/sdcard/`

### :movie_camera: Gerando o Timelapse com Python

Para gerar o timelapse com as imagens capturadas roda:

```bash
python3 timelapse.py
```

O script coleta todas as imagens do diretório especificado e gera um vídeo `.mp4` com **30 FPS**:

```bash
Input:  ./imagens/
Output: timelapse.mp4
```

## :adhesive_bandage: Solução de Problemas (Troubleshooting)

**Problema** |  **Causa Possível** | **Solução**
:-------------- | :-------------------: | -----------:
LCD exibindo caracteres estranhos | Conexão incorreta nos pinos SDA/SCL | Verifique os pinos D21 (SDA) e D22 (SCL)
Servidor da câmera não acessível | Falha na inicialização da câmera ou Wi-Fi | Reinicie a ESP32-CAM e verifique SSID/senha
Timelapse com erro de leitura de imagem | Caminho incorreto ou imagens corrompidas | Verifique o diretório de entrada e permissões

## 📄 Licença

Este projeto é de uso educacional e livre para fins acadêmicos.
Sinta-se à vontade para reutilizar o código, citando a autoria original.
