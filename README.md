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
  - [:keyboard: Operação do Controlador Principal](#-controlador-principal-esp32)
  - [:camera_flash: Operação do Módulo de Câmera](#-controlador-principal-esp32)
  - [:movie_camera: Gerando o Timelapse com Python](#movie_camera-gerando-o-timelapse-com-python)
- [:adhesive_bandage: Solução de Problemas (Troubleshooting)](#adhesive_bandage-solução-de-problemas-troubleshooting)
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
  - Controle de termico e de umidade (via **GPIOs**)
  - Comunicação com a **ESP32-CAM** via rede Wi-Fi
  - Envio dos dados para monitoramento

<p align="center"> 
  Pinout da <b>Esp32 main</b> para guiar quais portas conectar:
 </p>

<p align="center">
  <img height=300px src="/media/esp32_pin.jpg" alt="esp32 pinout"/>
</p>

<p align="center">
  <img height=150px src="/media/DHT11.png" alt="DHT11 pinout"/>
</p>

Segundo o pinout da esp32 deve conectar:

- **SDA** do LCD com a porta **D21**
- **SCL** do LCD na porta **D22** da esp32
- **Data pin** do DHT11 pa porta **D4** da esp32
- **Positivo** da Peltier quente na porta **D25** da esp32
- **Positivo** da Peltier fria na porta **D26** da esp32

### 📷 Módulo esp32-CAM

- Módulo com câmera OV2640
- Responsável por capturar imagens periodicamente
- As imagens são armazenadas localmente ou enviadas via servidor HTTP
- Posteriormente, são usadas para gerar um **timelapse** com script Python

## 🖥️ Setup do Ambiente de Desenvolvimento

### 🆔 Usando a IDE do Arduino

1. Instale a [IDE do Arduino](https://www.arduino.cc/en/software)
2. Vá no **boad manager** e instale o *"esp32 by Espressif Systems"*
3. Selecione a placa:
   - Para o controlador: `ESP32 Dev Module`
   - Para a câmera: `AI Thinker ESP32-CAM`

4. Copie os arquivos do `src/` de cada diretorio dentro de um novo projeto arduino
5. Colar o que está escrito no `main.cpp` no arquivo `.ino`
6. Faça upload dos códigos correspondentes de cada módulo.

### 💻 Usando o VS Code com PlatformIO

1. Instale o [VS Code](https://code.visualstudio.com/)
2. Adicione a extensão **PlatformIO IDE**
3. Abra cada diretorio do codigo em uma aba diferente do **VS Code**
4. Compile e envie para o dispositivo usando o botão na parte inferior ***PlatformIO: Upload***
5. Abra o monitor serial pelo botão ***PlatformIO: Serial Monitor***

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

Para gerar o timelapse com as imagens capturadas é primeiro preciso iniciar o `.venv` com o comando no terminal já dentro do diretorio do projeto:

```zsh
source .venv/bin/activate
```

Após isso basta rodar o o programa de python com as imagens no diretorio certo:

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
