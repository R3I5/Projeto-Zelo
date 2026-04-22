#ifndef PINS_H
#define PINS_H

// =========================
// RTC - I2C
// =========================
#define I2C_SDA 21
#define I2C_SCL 22

// =========================
// DHT
// =========================
#define DHT_PIN 15
#define DHT_TYPE DHT11

// =========================
// Display GC9A01 - SPI
// =========================
#define TFT_SCLK 18
#define TFT_MOSI 23
#define TFT_CS   27
#define TFT_DC   26
#define TFT_RST  25

#define USE_TFT_BLK false
#define TFT_BLK 13

#define TFT_ROTATION 0

#endif