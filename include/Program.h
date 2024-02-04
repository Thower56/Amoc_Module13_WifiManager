#pragma once
#include <MyWifiManager.h>
#include <ServeurWeb.h>
#include <Button.h>
#include <MQTT.h>
#include <Utilitaire.h>
#include <BME.h>

class Program{
public:
    Program();
    void loop();
private:
    int m_TemperatureMax;
    MyWifiManager* m_WifiManager;
    ServeurWeb* m_ServeurWeb;
    Button* m_Button;
    MQTT* m_MQTT;
    Timer* m_TimerToSend;
    BME* m_BME;
};