#pragma once
#include <Arduino.h>
#include <WiFiManager.h>
#include <uri/UriRegex.h>
#include <functional>
#include <ServeurWeb.h>

class MyWifiManager {
public:
    typedef std::function<void(void)> TFunction;
    MyWifiManager(){}
    MyWifiManager(IPAddress p_IpPortal, IPAddress p_Passerelle, IPAddress p_Masque){}
private:
    void setSaveParamsCallBack();
    void setAPCallBack();
    WiFiManager* m_wifiManager;
    ServeurWeb* m_serveurWeb;
    WiFiManagerParameter m_parametrePersonnalise;
    char const* SSIDPortail;
    char const* motPasseAPPortail;
};