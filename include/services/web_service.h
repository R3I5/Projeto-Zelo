#ifndef WEB_SERVICE_H
#define WEB_SERVICE_H

#include <WiFi.h>
#include <WebServer.h>

// Serviço responsável por criar uma interface web simples embarcada,
// exibindo hora, temperatura e status dos módulos do sistema.

class WebService {
private:
    WebServer server;
    String currentTime;
    float currentTemperature;
    bool rtcOnline;
    bool dhtOnline;
    bool displayOnline;

    void setupRoutes();
    String buildHtml();
    String buildJson();

public:
    WebService();

    void beginAccessPoint(const char* ssid, const char* password);
    void beginServer();
    void handleClient();

    void updateData(const String& time, float temperature, bool rtcStatus, bool dhtStatus, bool displayStatus);

    String getIP();
};

#endif