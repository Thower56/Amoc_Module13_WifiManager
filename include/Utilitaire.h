#pragma once
#include <Arduino.h>
#include <functional>
#include "FS.h"
#include <LittleFS.h>
#include <Config.h>


class Timer{
public:
    typedef std::function<void(void)> THandlerFunction;
    Timer(double p_second, THandlerFunction p_function);
    void tick();
private:
    THandlerFunction m_function;
    long m_derniereDateChangement;
    int m_second;
};

String readJson(fs::FS &fs, const char * path);
void writeJson(fs::FS &fs, const char * path, const String p_Json);
void editJsonPart(fs::FS &fs, const char * path, const String p_Key, const String p_Value);
void ajouterFichiersStatiques(String const& p_debutNomFichier) ;
void ajouterFichiersStatiques(String const& p_debutNomFichier, String const& p_repertoireCourant, File& p_repertoire);

void checkRacine();