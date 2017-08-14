#pragma once
#include "ofMain.h"

/* Viiva.h
 * Viiva -luokka sekä kaksi säiliö -luokkaa datalle: 
 * ViivanPiste ja ViivanOminaisuus
 */

/* ViivanPiste
 * viivan pisteiden säilytykseen
 */
struct ViivanPiste {
    float paine;
    ofPoint sijainti;
    ViivanPiste(ofPoint sijainti_ = ofPoint(), float paine_ = 0);
};

/* ViivanOminaisuus
 * yleinen säiliö -luokka erilaisille viivan ominaisuuksille
 * Säiliöön varastoidaan myös arvosta lasketut analyysit kuten
 * keskiarvo ja keskihajonta
 */

struct ViivanOminaisuus {
    float arvo;
    float keskiarvo;
    float keskihajonta;
    float keskihajonnanKeskihajonta;
    float konvergenssi;
    ViivanOminaisuus();
};


/* Viiva
 * Viiva -luokka on kuvaus yhdestä käyttäjän piirtämästä viivasta.
 * Viiva -luokassa säilytettään viivan pisteitä ja niistä johdettuja 
 * ominaisuusarvoja. Ominaisuusarvoja voidaan analysoida ja tiedot 
 * tallennetaan Viivan sisälle. 
 * 
 * Koska Viivasta saatu tieto on pitkittäistä ja poikittaista, Viiva -luokka
 * pyrkii tarjoamaan työkalut tiedon jäsentämiseen pistekohtaisesti ja viivakohtaisesti
 * esim pisteet[2],paksuus[2].arvo, sumeus[2].arvo kertoo kaiken yhdestä pisteestä kun taas
 * haeKeskiarvot(&paksuus); palauttaa kaikki paksuus -ominaisuuden keskiarvot
 */

struct Viiva {
    vector<ViivanPiste> pisteet;
    vector<ViivanOminaisuus> paksuus;
    vector<ViivanOminaisuus> sumeus;
    ofColor vari;

    void lisaaPiste(ofPoint paikka, float paine);
    
    ViivanPiste haeViimeisinPiste() const;
    ViivanOminaisuus haeViimeisinPaksuus() const;
    ViivanOminaisuus haeViimeisinSumeus() const;
    
    vector<float> haeArvot(const vector<ViivanOminaisuus>* const ominaisuus) const;
    vector<float> haeArvot(const vector<ViivanOminaisuus>* const ominaisuus, unsigned int otanta) const;
    
    vector<float> haeKeskiarvot(const vector<ViivanOminaisuus>* const ominaisuus) const;
    vector<float> haeKeskihajonnat(const vector<ViivanOminaisuus>* const ominaisuus) const;
    vector<float> haeKeskihajonnat(const vector<ViivanOminaisuus>* const ominaisuus, unsigned int otanta) const;
    vector<float> haeKeskihajonnanKeskihajonnat(const vector<ViivanOminaisuus>* const ominaisuus) const;
    vector<float> haeKonvergenssit(const vector<ViivanOminaisuus>* const ominaisuus) const;
    

protected:
    
};
