#include "services/display_service.h"
#include <math.h>
#include <stdio.h>

void DisplayService::renderMainScreen(GC9A01Display& display, const DateTime& now, float temperature) {
    display.clear(GC9A01A_BLACK);
    display.drawCenteredTitle("Projeto Zelo", GC9A01A_CYAN);

    char timeBuffer[9];
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

    display.showText(35, 80, "Hora:", GC9A01A_WHITE, 2);
    display.showText(35, 110, String(timeBuffer), GC9A01A_YELLOW, 3);

    display.showText(35, 160, "Temp:", GC9A01A_WHITE, 2);

    if (isnan(temperature)) {
        display.showText(35, 190, "Erro leitura", GC9A01A_RED, 2);
    } else {
        display.showText(35, 190, String(temperature, 1) + " C", GC9A01A_GREEN, 3);
    }
}