#include <Program.h>


Program::Program(){
    Serial.begin(115200);
    ajouterFichiersStatiques("/");
    checkRacine();
    IPAddress adresseIP(192,168,0,1);
    IPAddress passerelle(192,168,23,1);
    IPAddress masque(255,255,255,0);

    m_BME = new BME();
    m_WifiManager = new MyWifiManager(adresseIP,passerelle,masque);
    m_ServeurWeb = new ServeurWeb();
    m_Button = new Button(25);
    m_Button->setFunction([this](){ESP.restart(); m_WifiManager->eraseConfig(); });
    m_Joystick = new Joystick(36,39);

    nomUnique = String(ESP.getEfuseMac(), HEX);
    m_MQTT = new MQTT(nomUnique);

    

    m_MQTT->setFunction({[this](String p_topic, String p_Payload){ToggleLed(p_topic, p_Payload);},
                        [this](String p_topic, String p_Payload){Temperature(p_topic, p_Payload);},
                        [this](String p_topic, String p_Payload){TemperatureMax(p_topic, p_Payload);},
                        [this](String p_topic, String p_Payload){ReadJoyStick(p_topic, p_Payload);}});

    m_MQTT->setCallback();
    m_MQTT->setConfig("/sauvegarde/Configuration.json");

    if(WiFi.isConnected()){
        m_ServeurWeb->begin();
        m_WifiManager->getIp();
    }

    m_TimerToSend = new Timer(5, [this](){m_MQTT->envoieMessage(nomUnique + "/temperature", (String)m_BME->getTemperature());});
    m_TimerToSendJoystick = new Timer(0.5, [this](){m_MQTT->envoieMessage(nomUnique + "/joystickX", (String)m_Joystick->getAxisX());});
    pinMode(LED_BUILTIN, OUTPUT);
}

void Program::ReadJoyStick(String p_topic, String p_Payload){
    if(String(p_topic) == nomUnique + "/joystickX"){
        Serial.print("Joystick X: ");
        Serial.println(p_Payload);
    }
};

void Program::ToggleLed(String p_topic, String p_Payload){
    if (String(p_topic) == "broadcast/led") {
        if (p_Payload == "on") {
            digitalWrite(LED_BUILTIN, HIGH);
        } else if (p_Payload == "off") {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
};
void Program::Temperature(String p_topic, String p_Payload){
    if(String(p_topic) == nomUnique + "/temperature"){
        if(p_Payload.toInt() > m_TemperatureMax){
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else{
            digitalWrite(LED_BUILTIN, LOW);
        }
        Serial.print("La temperature recus: ");
        Serial.println(p_Payload);
    }
};
void Program::TemperatureMax(String p_topic, String p_Payload){
    if(String(p_topic) == (nomUnique + "/temperature/max")){
        m_TemperatureMax = p_Payload.toInt();
        Serial.print("Temperature Max: ");
        Serial.println(m_TemperatureMax);
        editJsonPart(LittleFS, "/sauvegarde/Configuration.json", "temperature_max", String(m_TemperatureMax));
    }
};

void Program::loop(){
    if(WiFi.isConnected()){
        m_ServeurWeb->tick();
        m_Button->tick();
        if(m_MQTT->reconnectMQTTSiNecessaire()){
            m_MQTT->loop();
            m_TimerToSend->tick();
            m_TimerToSendJoystick->tick();
        }
    }
}