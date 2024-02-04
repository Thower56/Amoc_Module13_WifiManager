#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <functional>

class MQTT{
public:
    typedef std::function<void(char* topic, byte* payload, unsigned int length)> Callback;
    MQTT(String p_NomUnique);
    bool reconnectMQTTSiNecessaire();
    void envoieMessage();
    void envoieMessage(String p_Topic, String p_Payload);
    void setCallback(Callback p_Callback);
    void incriptionTopic(String p_Topic);
    void setConfig(String p_fileName);
    void getTopicList();
    void loop();
private:
    WiFiClient* m_wifiClient;
    PubSubClient* m_pubSubClient;
    String m_NomUnique;
    unsigned long lastSentMessageDate;
    unsigned long messageId;
};