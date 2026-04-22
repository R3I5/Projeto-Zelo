#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

// Módulo responsável pela leitura de temperatura do sensor DHT,
// abstraindo a biblioteca utilizada no hardware.

#include <DHT.h>

class DHTSensor {
private:
    DHT dht;

public:
    DHTSensor(uint8_t pin, uint8_t type);
    void begin();
    float readTemperature();
};

#endif