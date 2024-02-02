#include <MyWifiManager.h>
#include <Utilitaire.h>
#include <Config.h>

MyWifiManager::MyWifiManager(){}

MyWifiManager::MyWifiManager(IPAddress p_IpPortal, IPAddress p_Passerelle, IPAddress p_Masque){
    m_wifiManager = new WiFiManager();
    m_wifiManager->setAPStaticIPConfig(p_IpPortal, p_Passerelle, p_Masque);
    m_wifiManager->setParamsPage(true);
    m_wifiManager->autoConnect(WIFI_SSID_SCHOOL, WIFI_PASSWORD_SCHOOL);
}

void MyWifiManager::setParametrePersonnaliser(WiFiManagerParameter& p_parametrePersonnaliser){
    m_parametrePersonnalise = &p_parametrePersonnaliser;
    m_wifiManager->addParameter(m_parametrePersonnalise);
};

void MyWifiManager::setMySaveParamsCallBack(){
    m_wifiManager->setSaveParamsCallback([this](){
        writeJson(LittleFS, "/sauvegarde/Configuration.json", m_parametrePersonnalise->getValue()); 
    }); 
};

void MyWifiManager::setMyAPCallBack(){
    m_wifiManager->setAPCallback([this](WiFiManager* p_WifiManager){
        Serial.println("Connexion au reseau Wifi echoue, demarrage du Portail...");
    });
};

void MyWifiManager::getIp(){
    Serial.print("Connecté au réseau WiFi, adresse IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("");
}

void MyWifiManager::eraseConfig(){
    m_wifiManager->erase();
};