#ifndef GC9A01_DISPLAY_H
#define GC9A01_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>

// Módulo responsável por abstrair o display GC9A01.

class GC9A01Display {
private:
    Adafruit_GC9A01A display;

public:
    GC9A01Display(int8_t csPin, int8_t dcPin, int8_t rstPin);

    bool begin(uint8_t rotation = 0, uint32_t spiFrequency = 4000000);
    void clear(uint16_t color = GC9A01A_BLACK);
    void showText(int16_t x, int16_t y, const String& text, uint16_t color = GC9A01A_WHITE, uint8_t textSize = 1);
    void drawCenteredTitle(const String& title, uint16_t color = GC9A01A_CYAN);
};

#endif