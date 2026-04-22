#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>

#include "config/pins.h"
#include "drivers/rtc_manager.h"
#include "drivers/dht_sensor.h"
#include "drivers/gc9a01_display.h"
#include "services/display_service.h"
#include "services/web_service.h"

// Arquivo principal do projeto.
// Responsável por inicializar RTC, DHT, display GC9A01 e interface web,
// exibindo hora e temperatura na tela física e no navegador.

RTCManager rtcManager;
DHTSensor dhtSensor(DHT_PIN, DHT_TYPE);
GC9A01Display tft(TFT_CS, TFT_DC, TFT_RST);
DisplayService displayService;
WebService webService;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("===== INICIO DO SISTEMA =====");

    // RTC em I2C
    Wire.begin(I2C_SDA, I2C_SCL);

    // Display em SPI
    SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
    SPI.setFrequency(4000000);

    // Reset manual curto
    pinMode(TFT_RST, OUTPUT);
    digitalWrite(TFT_RST, LOW);
    delay(50);
    digitalWrite(TFT_RST, HIGH);
    delay(150);

    dhtSensor.begin();

    if (!rtcManager.begin())
    {
        Serial.println("Erro: RTC nao encontrado.");
    }
    else
    {
        Serial.println("RTC inicializado com sucesso.");
    }

    if (!tft.begin(TFT_ROTATION, 4000000))
    {
        Serial.println("Erro: display GC9A01 nao inicializado.");
        while (true)
        {
            delay(1000);
        }
    }

    tft.clear(GC9A01A_BLACK);
    tft.drawCenteredTitle("Projeto Zelo", GC9A01A_CYAN);
    tft.showText(35, 120, "Inicializando...", GC9A01A_WHITE, 2);

    webService.beginAccessPoint("Zelo-ESP32", "12345678");
    webService.beginServer();

    Serial.println("Display inicializado com sucesso.");
    Serial.print("Interface web disponivel em: ");
    Serial.println(webService.getIP());

    delay(1500);
}

void loop()
{
    DateTime currentTime = rtcManager.now();
    float temperature = dhtSensor.readTemperature();

    char timeBuffer[9];
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d",
             currentTime.hour(), currentTime.minute(), currentTime.second());

    String currentTimeStr = String(timeBuffer);

    Serial.print("Hora: ");
    Serial.println(currentTimeStr);

    Serial.print("Temperatura: ");
    Serial.println(temperature);

    displayService.renderMainScreen(tft, currentTime, temperature);

    webService.updateData(
        currentTimeStr,
        temperature,
        true,
        !isnan(temperature),
        true);

    webService.handleClient();

    delay(1000);
}