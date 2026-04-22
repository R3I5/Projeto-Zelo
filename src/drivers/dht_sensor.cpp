#include "drivers/dht_sensor.h"
#include <Arduino.h>

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DHTSensor::begin() {
    dht.begin();
}

float DHTSensor::readTemperature() {
    return dht.readTemperature();
}