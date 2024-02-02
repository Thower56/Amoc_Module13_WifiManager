#include <Button.h>
#include <Arduino.h>

Button::Button(uint8_t p_pinButton):
    m_boutonPresse(false),
    etatBouton (0),
    derniereDateChangement(0),
    dernierEtatBouton(HIGH),
    dernierEtatStableBouton(HIGH),
    delaiMinPression(25)
{
    m_pin = p_pinButton;
    pinMode(m_pin, INPUT);
};

int Button::getPin(){
    return m_pin;
};
void Button::setFunction(THandlerFunction p_fn){
    m_fn = p_fn;
};
void Button::tick(){

    int etatBouton = digitalRead(getPin());
    long dateActuelle = millis();

    if (etatBouton != dernierEtatBouton) {
        derniereDateChangement = dateActuelle;
        dernierEtatBouton = etatBouton;
    }

    if(dateActuelle - derniereDateChangement > delaiMinPression && dateActuelle - derniereDateChangement < delaiMinPression * 1000 ) {
        if (dernierEtatStableBouton == HIGH && etatBouton == LOW) {
            Serial.println("Click!");
            Serial.println("");
            m_fn();
        } 
        dernierEtatStableBouton = etatBouton;
    }
};