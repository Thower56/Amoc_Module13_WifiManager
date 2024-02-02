#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

class MQTT{
public:
    MQTT(String p_NomUnique);
    bool reconnectMQTTSiNecessaire();
    void envoieMessage();
    void loop();
private:
    WiFiClient* m_wifiClient;
    PubSubClient* m_pubSubClient;
    String m_NomUnique;
    unsigned long lastSentMessageDate;
    unsigned long messageId;
};