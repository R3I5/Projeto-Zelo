#include "drivers/gc9a01_display.h"

GC9A01Display::GC9A01Display(int8_t csPin, int8_t dcPin, int8_t rstPin)
    : display(csPin, dcPin, rstPin) {}

bool GC9A01Display::begin(uint8_t rotation, uint32_t spiFrequency) {
    display.begin(spiFrequency);
    display.setRotation(rotation);
    display.setTextWrap(false);
    display.fillScreen(GC9A01A_BLACK);
    return true;
}

void GC9A01Display::clear(uint16_t color) {
    display.fillScreen(color);
}

void GC9A01Display::showText(int16_t x, int16_t y, const String& text, uint16_t color, uint8_t textSize) {
    display.setCursor(x, y);
    display.setTextColor(color);
    display.setTextSize(textSize);
    display.print(text);
}

void GC9A01Display::drawCenteredTitle(const String& title, uint16_t color) {
    int16_t x1, y1;
    uint16_t w, h;

    display.setTextSize(2);
    display.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);

    int16_t x = (240 - w) / 2;
    int16_t y = 20;

    display.setCursor(x, y);
    display.setTextColor(color);
    display.print(title);
}