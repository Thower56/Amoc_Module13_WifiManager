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

    m_MQTT->setConfig("/sauvegarde/Configuration.json");

    m_MQTT->setCallback(
        [this](char* topic, byte* payload, unsigned int length) {
                Serial.print("Message reçu [");
                Serial.print(topic);
                Serial.print("] ");
                String payloadString = "";

                for (int i = 0; i < length; i++) {
                payloadString += (char)payload[i];
                }
                Serial.println(payloadString);

                // DEL
                if (String(topic) == "broadcast/led") {
                if (payloadString == "on") {
                    digitalWrite(LED_BUILTIN, HIGH);
                } else if (payloadString == "off") {
                    digitalWrite(LED_BUILTIN, LOW);
                }
                }

                //Temperature
                if(String(topic) == "ESP32{id}/temperature"){
                    if(payloadString.toInt() > m_TemperatureMax){
                        digitalWrite(LED_BUILTIN, HIGH);
                    }
                    else{
                        digitalWrite(LED_BUILTIN, LOW);
                    }
                    Serial.print("La temperature recus: ");
                    Serial.println(payloadString);
                }

                //Temperature Max
                if(String(topic) == "ESP32{id}/temperature/max"){
                    m_TemperatureMax = payloadString.toInt();
                    editJsonPart(LittleFS, "/sauvegarde/statusCompactor.json", "temperature_max", String(m_TemperatureMax));
                }
            }
        );

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