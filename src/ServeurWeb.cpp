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

void ServeurWeb::ajouterFichiersStatiques(String const& p_debutNomFichier,String const& p_repertoireCourant,File& p_repertoire){
  if (!p_repertoire) return;

  Serial.println(String("Traitement du répertoire : ") + p_repertoire.name());

  File fichier = p_repertoire.openNextFile();
  while (fichier) {
    String nomFichier = p_repertoireCourant + "/" + String(fichier.name());
    if (fichier.isDirectory()) {
      ajouterFichiersStatiques(p_debutNomFichier, p_repertoireCourant + "/" + fichier.name(), fichier);
    } else {
      if (nomFichier.startsWith(p_debutNomFichier)) {
        Serial.println(String("Ajout du fichier statique : ") + nomFichier + " pour l'URI " + toURI(nomFichier));
        this->m_webServer->serveStatic(toURI(nomFichier).c_str(), FS,
                                       nomFichier.c_str());
      }
    }
    fichier.close();
    fichier = p_repertoire.openNextFile();
  }

  p_repertoire.close();
};

void ServeurWeb::ressourceNonTrouvee(const String& p_nomRessource) {
  Serial.println("Ressource '" + p_nomRessource + "' non trouvée !");
  this->m_webServer->send(404, "text/plain",
                          "Ressource '" + p_nomRessource + "' non trouvée !");
}

void ServeurWeb::begin(){
  this->m_webServer->begin();
}