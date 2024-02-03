#include <BME.h>
#include <Config.h>

BME::BME(){
    m_bme = new Adafruit_BME280();
    m_bme->begin(0x76);
};
float BME::getTemperature(){
    return m_bme->readTemperature();
};
float BME::getPressure(){
    return m_bme->readPressure();
};
float BME::getAltitude(){
    return m_bme->readAltitude(SEALEVELPRESSURE_HPA);
};
float BME::getHumidity(){
    return m_bme->readTemperature();
};