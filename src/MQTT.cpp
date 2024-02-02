#include <MQTT.h>
#include <config.h>

MQTT::MQTT(String p_NomUnique){
    lastSentMessageDate = 0;
    messageId = 0;
    m_wifiClient = new WiFiClient();
    m_pubSubClient = new PubSubClient(*m_wifiClient);
    m_pubSubClient->setBufferSize(1024);
    m_pubSubClient->setServer(MQTT_SERVER, MQTT_PORT);
    m_NomUnique = p_NomUnique;
};
bool MQTT::reconnectMQTTSiNecessaire(){
    
  if (!m_pubSubClient->connected()) {
    Serial.println("Connexion au broker MQTT...");
    if (m_pubSubClient->connect(m_NomUnique.c_str(), MQTT_USER, MQTT_PASSWORD,
                              (m_NomUnique + "/status").c_str(), 0, 0,
                              "offline")) {
      Serial.println("Connecté au broker MQTT");
      m_pubSubClient->publish((m_NomUnique + "/status").c_str(), "online");
      m_pubSubClient->subscribe("broadcast/#");
      m_pubSubClient->setCallback(
          [](char* topic, byte* payload, unsigned int length) {
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
          });
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

void MQTT::loop(){
    m_pubSubClient->loop();
};