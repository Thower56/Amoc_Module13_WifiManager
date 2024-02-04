#include <MQTT.h>
#include <config.h>
#include <Utilitaire.h>
#include <ArduinoJson.h>

MQTT::MQTT(String p_NomUnique){
    lastSentMessageDate = 0;
    messageId = 0;
    m_wifiClient = new WiFiClient();
    m_pubSubClient = new PubSubClient(*m_wifiClient);
    m_NomUnique = p_NomUnique;
};

void MQTT::incriptionTopic(String p_Topic){
  m_pubSubClient->subscribe(p_Topic.c_str());
};

void MQTT::setCallback(Callback p_Callback){
  m_pubSubClient->setCallback(p_Callback);
};

void MQTT::setConfig(String p_fileName){
  String json = readJson(LittleFS, p_fileName.c_str());
  StaticJsonDocument<500> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    Serial.println("Configuration MQTT non chargée");
    return;
  }
  else{
    m_pubSubClient->setServer(doc["mqtt_server"].as<String>().c_str(), doc["mqtt_port"]);

    JsonArray topics = doc["mqtt_topic"].as<JsonArray>();
    for(int i = 0; i < topics.size(); i++){
      Serial.print("Inscription au topic: ");
      Serial.println(topics[i].as<String>());
      incriptionTopic(topics[i].as<String>());
    }
    Serial.println("Configuration MQTT chargée");
    Serial.print("Nom unique: ");
    Serial.println(m_NomUnique);
    Serial.print("mqtt_server: ");
    Serial.println(doc["mqtt_server"].as<String>());
    Serial.print("mqtt_port: ");
    Serial.println(doc["mqtt_port"].as<int>());

  }
 
};

bool MQTT::reconnectMQTTSiNecessaire(){
    
  if (!m_pubSubClient->connected()) {
    Serial.println("Connexion au broker MQTT...");
    if (m_pubSubClient->connect(m_NomUnique.c_str(), MQTT_USER, MQTT_PASSWORD,
                              (m_NomUnique + "/status").c_str(), 0, 0,
                              "offline")) {
      Serial.println("Connecté au broker MQTT");
      m_pubSubClient->publish((m_NomUnique + "/status").c_str(), "online");

    } else {
      Serial.print("Echec de connexion au broker MQTT : ");
      Serial.println(m_pubSubClient->state());
      Serial.println("Nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }

  return m_pubSubClient->connected();
};
void MQTT::envoieMessage(){
  String topic = m_NomUnique + "/data";
  String payload = String("Hello World! - ") + String(messageId++);
  Serial.print("Envoi du message [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(payload);
  m_pubSubClient->publish(topic.c_str(), payload.c_str());
};

void MQTT::envoieMessage(String p_Topic, String p_Payload){
  Serial.print("Envoi du message [");
  Serial.print(p_Topic);
  Serial.print("] ");
  Serial.println(p_Payload);
  m_pubSubClient->publish(p_Topic.c_str(), p_Payload.c_str());
};

void MQTT::loop(){
    m_pubSubClient->loop();
};