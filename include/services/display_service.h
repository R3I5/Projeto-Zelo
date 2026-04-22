#ifndef DISPLAY_SERVICE_H
#define DISPLAY_SERVICE_H

#include "drivers/gc9a01_display.h"
#include <RTClib.h>

// Serviço responsável por organizar o conteúdo exibido no display.

class DisplayService {
public:
    void renderMainScreen(GC9A01Display& display, const DateTime& now, float temperature);
};

#endif