#include "drivers/rtc_manager.h"
#include <Arduino.h>

bool RTCManager::begin() {
    if (!rtc.begin()) {
        return false;
    }

    if (rtc.lostPower()) {
        adjustToCompileTime();
    }

    return true;
}

DateTime RTCManager::now() {
    return rtc.now();
}

bool RTCManager::lostPower() {
    return rtc.lostPower();
}

void RTCManager::adjustToCompileTime() {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}