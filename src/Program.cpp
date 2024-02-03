#include <Program.h>

Program::Program(){
    Serial.begin(115200);


    IPAddress adresseIP(192,168,0,1);
    IPAddress passerelle(192,168,23,1);
    IPAddress masque(255,255,255,0);

    m_BME = new BME();
    m_WifiManager = new MyWifiManager(adresseIP,passerelle,masque);
    m_ServeurWeb = new ServeurWeb();
    m_Button = new Button(25);
    m_Button->setFunction([this](){ESP.restart(); m_WifiManager->eraseConfig();});

    String nomUnique = String("ESP32Client") + String(ESP.getEfuseMac(), HEX);
    m_MQTT = new MQTT(nomUnique);

    if(WiFi.isConnected()){
        m_ServeurWeb->begin();
        m_WifiManager->getIp();
    }

    m_TimerToSend = new Timer(5, [this](){m_MQTT->envoieMessage();});

     pinMode(LED_BUILTIN, OUTPUT);
}

void Program::loop(){
    if(WiFi.isConnected()){
        m_ServeurWeb->tick();
        m_Button->tick();
        if(m_MQTT->reconnectMQTTSiNecessaire()){
            m_MQTT->loop();
            m_TimerToSend->tick();
        }
    }
}