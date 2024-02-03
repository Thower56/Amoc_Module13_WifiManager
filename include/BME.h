#pragma once
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class BME{
public:
    BME();
    float getTemperature();
    float getPressure();
    float getAltitude();
    float getHumidity();
private:
    Adafruit_BME280* m_bme;
};