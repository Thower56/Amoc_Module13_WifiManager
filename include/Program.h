#pragma once
#include <MyWifiManager.h>
#include <ServeurWeb.h>

class Program{
public:
    Program();
    void loop();
private:
MyWifiManager* m_WifiManager;
ServeurWeb* m_ServeurWeb;
};