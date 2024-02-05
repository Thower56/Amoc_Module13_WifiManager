#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <functional>
#include <vector>

class MQTT{
public:
    typedef std::function<void(String p_Topic, String p_Payload)> CustomFunction;
    MQTT(String p_NomUnique);
    bool reconnectMQTTSiNecessaire();
    void envoieMessage();
    void envoieMessage(String p_Topic, String p_Payload);
    void setCallback();
    void incriptionTopic(String p_Topic);
    void setConfig(String p_fileName);
    void getTopicList();
    void loop();
    void setFunction(std::vector<CustomFunction> m_function);
private:
    WiFiClient* m_wifiClient;
    PubSubClient* m_pubSubClient;
    String m_NomUnique;
    unsigned long lastSentMessageDate;
    unsigned long messageId;
    String m_serverAddress;
    int m_serverPort;
    String m_nomUser;
    String m_Password;
    std::vector<CustomFunction> m_ListFunction;
    std::vector<String> m_ListeTopics;
};