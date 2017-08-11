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
    ViivanPiste(float x_=0, float y_=0, float paine_=0 );
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


//aseta viimeisen jäsenen keskiarvo, keskihajonta ja keskihajonnan keskihajonta sekä konvergenssi
void laskeTilastoluvut(vector<ViivanOminaisuus>& tilasto);


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

    void lisaaPiste(float x, float y, float paine);
    
    ViivanPiste haeViimeisinPiste();
    ViivanOminaisuus haeViimeisinPaksuus();
    ViivanOminaisuus haeViimeisinSumeus();
    
    vector<float> haeArvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeArvot(vector<ViivanOminaisuus>* ominaisuus, unsigned int otanta);
    vector<float> haeKeskiarvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus, unsigned int otanta);
    vector<float> haeKeskihajonnanKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKonvergenssit(vector<ViivanOminaisuus>* ominaisuus);
    
    size_t size() {return pisteet.size();}

protected:
    vector<ViivanPiste> pisteet;
    vector<ViivanOminaisuus> paksuus;
    vector<ViivanOminaisuus> sumeus;
    vector<ofColor> vari;
    
};
