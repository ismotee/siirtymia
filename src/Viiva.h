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
    float x,y,paine;
    ViivanPiste();
    ViivanPiste(float x_, float y_, float paine_);
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
    vector<ofColor> vari;

    void lisaaPiste(float x, float y, float paine);
    vector<float> haeArvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskiarvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnanKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKonvergenssit(vector<ViivanOminaisuus>* ominaisuus);
};
