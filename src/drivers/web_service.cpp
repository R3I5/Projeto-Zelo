#include "services/web_service.h"
#include <math.h>

WebService::WebService()
    : server(80), currentTime("--:--:--"), currentTemperature(NAN),
      rtcOnline(false), dhtOnline(false), displayOnline(false) {}

void WebService::beginAccessPoint(const char *ssid, const char *password)
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
}

String WebService::getIP()
{
    return WiFi.softAPIP().toString();
}

void WebService::setupRoutes()
{
    server.on("/", [this]()
              { server.send(200, "text/html; charset=utf-8", buildHtml()); });

    server.on("/api/status", [this]()
              { server.send(200, "application/json", buildJson()); });
}

void WebService::beginServer()
{
    setupRoutes();
    server.begin();
}

void WebService::handleClient()
{
    server.handleClient();
}

void WebService::updateData(const String &time, float temperature, bool rtcStatus, bool dhtStatus, bool displayStatus)
{
    currentTime = time;
    currentTemperature = temperature;
    rtcOnline = rtcStatus;
    dhtOnline = dhtStatus;
    displayOnline = displayStatus;
}

String WebService::buildJson()
{
    String tempValue = isnan(currentTemperature) ? "null" : String(currentTemperature, 1);

    String json = "{";
    json += "\"time\":\"" + currentTime + "\",";
    json += "\"temperature\":" + tempValue + ",";
    json += "\"rtc\":" + String(rtcOnline ? "true" : "false") + ",";
    json += "\"dht\":" + String(dhtOnline ? "true" : "false") + ",";
    json += "\"display\":" + String(displayOnline ? "true" : "false");
    json += "}";

    return json;
}

String WebService::buildHtml()
{
    return R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Zelo - Monitoramento</title>
  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: Arial, sans-serif;
    }

    body {
      background: #f1f1f1;
      color: #1f2d3d;
    }

    .topbar {
      background: #1f36b7;
      color: white;
      padding: 20px 28px;
      font-size: 42px;
      font-weight: bold;
      border-top: 3px solid #7a00ff;
    }

    .page {
      padding: 24px;
      display: grid;
      grid-template-columns: 2.3fr 1fr;
      gap: 24px;
    }

    .card {
      background: #becaee;
      border-radius: 28px;
      padding: 24px;
      box-shadow: 0 2px 8px rgba(0,0,0,0.08);
    }

    .title {
      color: #1f36b7;
      font-size: 28px;
      font-weight: 800;
      margin-bottom: 18px;
    }

    .main-panel .title {
      font-size: 54px;
      margin-bottom: 24px;
    }

    .med-table {
      width: 100%;
      border-collapse: collapse;
      font-size: 20px;
    }

    .med-table th, .med-table td {
      border-bottom: 3px solid #1f36b7;
      border-right: 3px solid #1f36b7;
      padding: 14px;
      text-align: center;
      min-height: 52px;
    }

    .med-table th:last-child, .med-table td:last-child {
      border-right: none;
    }

    .med-table td {
      height: 74px;
      color: #333;
    }

    .standby {
      color: #6a6a6a;
      font-style: italic;
    }

    .right-column {
      display: flex;
      flex-direction: column;
      gap: 20px;
    }

    .status-item {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin: 18px 0;
      font-size: 18px;
      font-weight: bold;
    }

    .pill {
      color: white;
      font-size: 14px;
      font-weight: bold;
      padding: 8px 14px;
      border-radius: 999px;
      min-width: 62px;
      text-align: center;
    }

    .on { background: #0ecb67; }
    .off { background: #ff2957; }

    .bottom-grid {
      margin-top: 24px;
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 24px;
    }

    .metric-value {
      font-size: 38px;
      font-weight: bold;
      color: #1f36b7;
      margin-top: 14px;
    }

    .metric-sub {
      margin-top: 10px;
      font-size: 18px;
      color: #333;
    }

    .log-line {
      font-size: 18px;
      margin: 12px 0;
      font-weight: 600;
    }

    .highlight {
      color: #1f36b7;
      font-weight: bold;
    }

    @media (max-width: 980px) {
      .page {
        grid-template-columns: 1fr;
      }

      .bottom-grid {
        grid-template-columns: 1fr;
      }

      .main-panel .title {
        font-size: 40px;
      }
    }
  </style>
</head>
<body>
  <div class="topbar">ZELO</div>

  <div class="page">
    <div>
      <div class="card main-panel">
        <div class="title">MEDICAMENTOS</div>
        <table class="med-table">
          <thead>
            <tr>
              <th>Nome</th>
              <th>Quantidade</th>
              <th>Frequência</th>
              <th>Símbolo</th>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td class="standby">standby</td>
              <td class="standby">standby</td>
              <td class="standby">standby</td>
              <td class="standby">standby</td>
            </tr>
          </tbody>
        </table>
      </div>

      <div class="bottom-grid">
        <div class="card">
          <div class="title">Temperatura</div>
          <div class="metric-value" id="temperature">--.- C</div>
          <div class="metric-sub">Leitura atual do sensor DHT</div>
        </div>

        <div class="card">
          <div class="title">Horário</div>
          <div class="metric-value" id="time">--:--:--</div>
          <div class="metric-sub">Horário atual do RTC</div>
        </div>

        <div class="card">
          <div class="title">Wi-Fi</div>
          <div class="metric-value">AP Ativo</div>
          <div class="metric-sub">Interface embarcada em modo local</div>
        </div>
      </div>
    </div>

    <div class="right-column">
      <div class="card">
        <div class="title">SAÚDE ZELO</div>

        <div class="status-item">
          <span>Sensor RTC</span>
          <span class="pill" id="rtcStatus">OFF</span>
        </div>

        <div class="status-item">
          <span>Display</span>
          <span class="pill" id="displayStatus">OFF</span>
        </div>

        <div class="status-item">
          <span>Sensor DHT</span>
          <span class="pill" id="dhtStatus">OFF</span>
        </div>
      </div>

      <div class="card">
        <div class="title">LOG</div>
        <div class="log-line">Sistema web embarcado iniciado</div>
        <div class="log-line">RTC: <span class="highlight" id="logRtc">aguardando</span></div>
        <div class="log-line">DHT: <span class="highlight" id="logDht">aguardando</span></div>
        <div class="log-line">Display: <span class="highlight" id="logDisplay">aguardando</span></div>
      </div>
    </div>
  </div>

  <script>
    function setStatus(elementId, isOn) {
      const el = document.getElementById(elementId);
      el.textContent = isOn ? "ON" : "OFF";
      el.className = "pill " + (isOn ? "on" : "off");
    }

    async function updateData() {
      try {
        const response = await fetch('/api/status');
        const data = await response.json();

        document.getElementById('time').textContent = data.time || "--:--:--";
        document.getElementById('temperature').textContent =
          data.temperature === null ? "Erro" : `${data.temperature.toFixed(1)} C`;

        setStatus("rtcStatus", data.rtc);
        setStatus("dhtStatus", data.dht);
        setStatus("displayStatus", data.display);

        document.getElementById("logRtc").textContent = data.rtc ? "online" : "offline";
        document.getElementById("logDht").textContent = data.dht ? "online" : "offline";
        document.getElementById("logDisplay").textContent = data.display ? "online" : "offline";
      } catch (error) {
        console.error("Erro ao atualizar dados:", error);
      }
    }

    updateData();
    setInterval(updateData, 2000);
  </script>
</body>
</html>
)rawliteral";
}