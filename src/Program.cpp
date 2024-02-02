#include <Program.h>

Program::Program(){
    IPAddress adresseIP(192,168,0,1);
    IPAddress passerelle(192,168,23,1);
    IPAddress masque(255,255,255,0);
    m_WifiManager = new MyWifiManager(adresseIP,passerelle,masque);
    m_ServeurWeb = new ServeurWeb();
    if(WiFi.isConnected()){
        m_ServeurWeb->begin();
    }
}

void Program::loop(){
    if(WiFi.isConnected()){
        m_ServeurWeb->tick();
    }
}