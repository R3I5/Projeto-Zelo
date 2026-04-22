#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

// Módulo responsável por inicializar e consultar o RTC,
// fornecendo data e hora atuais para o sistema.

#include <RTClib.h>

class RTCManager {
private:
    RTC_DS3231 rtc;

public:
    bool begin();
    DateTime now();
    bool lostPower();
    void adjustToCompileTime();
};

#endif