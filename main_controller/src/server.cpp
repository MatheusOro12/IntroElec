#include "server.h"
#include <WebServer.h>
#include "sensors.h"
#include "control.h"

WebServer server(80);

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Controle Ambiental</title>
  <style>
    body { font-family: Arial; background: #f4f4f4; margin: 20px; }
    h2 { color: #333; }
    .box { background: white; padding: 20px; border-radius: 10px; width: 300px; }
    label { display:block; margin-top:10px; }
    input { width: 100%; padding:5px; }
    button { margin-top:15px; padding:8px 12px; }
  </style>
</head>
<body>
  <h2>Painel de Controle</h2>
  <div class="box">
    <p><b>Temperatura atual:</b> <span id="tAtual">--</span> °C</p>
    <p><b>Umidade atual:</b> <span id="uAtual">--</span> %</p>
    <form id="form">
      <label>Temperatura desejada:</label>
      <input type="number" id="temp" step="0.1" min="15" max="45">
      <label>Umidade desejada:</label>
      <input type="number" id="umid" step="0.1" min="20" max="80">
      <button type="submit">Atualizar</button>
    </form>
  </div>
<script>
const statusURL = "/status";
const setURL = "/set";

async function updateStatus() {
  const res = await fetch(statusURL);
  const data = await res.json();
  document.getElementById('tAtual').textContent = data.tempAtual;
  document.getElementById('uAtual').textContent = data.umidadeAtual;
  document.getElementById('temp').value = data.tempDesejada;
  document.getElementById('umid').value = data.umidadeDesejada;
}

document.getElementById('form').addEventListener('submit', async (e) => {
  e.preventDefault();
  const temp = document.getElementById('temp').value;
  const umid = document.getElementById('umid').value;
  await fetch(setURL, {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: `temp=${temp}&umid=${umid}`
  });
  updateStatus();
});

setInterval(updateStatus, 5000);
updateStatus();
</script>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleStatus() { //atualiza o que é mostrado no site
    float t = getTemperature();
    float h = getHumidity();
    float td = getTargetTemperature();
    float hd = getTargetHumidity();

    String json = "{";
    json += "\"tempAtual\":" + String(t, 1) + ",";
    json += "\"umidadeAtual\":" + String(h, 1) + ",";
    json += "\"tempDesejada\":" + String(td, 1) + ",";
    json += "\"umidadeDesejada\":" + String(hd, 1);
    json += "}";
    server.send(200, "application/json", json);
}

void handleSet() {// recebe o que foi modificado no site 
    if (server.hasArg("temp")) {
        setTargetTemperature(server.arg("temp").toFloat());
    }
    if (server.hasArg("umid")) {
        setTargetHumidity(server.arg("umid").toFloat());
    }
    server.send(200, "text/plain", "Valores atualizados");
}

void setupServer() { //inicia o servidor com os inderesos genericos
    server.on("/", handleRoot);
    server.on("/status", handleStatus);
    server.on("/set", HTTP_POST, handleSet);
    server.begin();
    Serial.println("Servidor iniciado");
}

void handleServer() { //atualiza o servidor com o metodo padrao do server
    server.handleClient();
}
