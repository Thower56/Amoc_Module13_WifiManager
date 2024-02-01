#pragma once
#include <Arduino.h>
#include <FS.h>

class WebServer;

class ServeurWeb{
    public:
    ServeurWeb();
    void modifierJson(String p_champ, String p_nouvelleValeur);
    void update();
    void tick();

    private:
    WebServer* m_webServer;
    void afficherRacine();
    void ajouterFichiersStatiques(String const& p_debutNomFichier);
    void ajouterFichiersStatiques(String const& p_debutNomFichier,
                                    String const& p_repertoireCourant,
                                    File& p_fichier);
                                    
    void ressourceNonTrouvee(String const& p_nomFichier);
};