#include "ServeurWeb.h"
#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <detail/RequestHandlersImpl.h>
#include <Config.h>
#include <uri/UriBraces.h>


#include <LittleFS.h>
#define FS LittleFS

String toURI(const String &path) {
  return path;
}


ServeurWeb::ServeurWeb()
{
  FS.begin(true);

  this->m_webServer = new WebServer(80);
  Serial.println("constructeur serveur");
  this->ajouterFichiersStatiques("/");
  this->m_webServer->on("/", HTTPMethod::HTTP_GET,
                        [this]() { this->afficherRacine(); });
}

void ServeurWeb::tick() { 
  this->m_webServer->handleClient(); 
}

void ServeurWeb::afficherRacine() {
  Serial.println("Réception requête");
  Serial.println(this->m_webServer->uri());

  this->m_webServer->sendHeader("Location", "index.html", true);
  this->m_webServer->send(301, "text/plain", "");
}

void ServeurWeb::ajouterFichiersStatiques(String const& p_debutNomFichier) {
  File racine = FS.open("/");
  ajouterFichiersStatiques(p_debutNomFichier, "", racine);
}

void ServeurWeb::ressourceNonTrouvee(const String& p_nomRessource) {
  Serial.println("Ressource '" + p_nomRessource + "' non trouvée !");
  this->m_webServer->send(404, "text/plain",
                          "Ressource '" + p_nomRessource + "' non trouvée !");
}

void ServeurWeb::begin(){
  this->m_webServer->begin();
}