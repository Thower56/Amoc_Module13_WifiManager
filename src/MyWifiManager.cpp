#include <MyWifiManager.h>
#include <Utilitaire.h>
#include <Config.h>

MyWifiManager::MyWifiManager(){}

MyWifiManager::MyWifiManager(IPAddress p_IpPortal, IPAddress p_Passerelle, IPAddress p_Masque){
    m_wifiManager->addParameter(&m_parametrePersonnalise);
    m_wifiManager->setAPStaticIPConfig(p_IpPortal, p_Passerelle, p_Masque);
    m_wifiManager->setParamsPage(true);
    m_wifiManager->autoConnect(WIFI_SSID_SCHOOL, WIFI_PASSWORD_SCHOOL);
}

void MyWifiManager::setSaveParamsCallBack(){
    m_wifiManager->setSaveParamsCallback([this](){
        writeJson(LittleFS, "/sauvegarde/Configuration.json", this->m_parametrePersonnalise.getValue()); 
    }); 
};

void MyWifiManager::setAPCallBack(){
    m_wifiManager->setAPCallback([this](WiFiManager* p_WifiManager){
        Serial.println("Connexion au reseau Wifi echoue, demarrage du Portail...");
    });
};