#pragma once
#include <Arduino.h>
#include <WiFiManager.h>
#include <uri/UriRegex.h>


class MyWifiManager {
public:

    MyWifiManager();
    MyWifiManager(IPAddress p_IpPortal, IPAddress p_Passerelle, IPAddress p_Masque);
    void setParametrePersonnaliser(WiFiManagerParameter& p_parametrePersonnaliser);
    void getIp();
    void eraseConfig();
private:
    void setMySaveParamsCallBack();
    void setMyAPCallBack();
    WiFiManager* m_wifiManager;
    WiFiManagerParameter* m_parametrePersonnalise;
};