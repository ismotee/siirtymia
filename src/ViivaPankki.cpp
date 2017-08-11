#include "ViivaPankki.h"

void ViivaPankki::lisaaMuokattavaPankkiin() {
    viivat.push_back(muokattava);
}

void ViivaPankki::aloitaUusiMuokattava() {    
    muokattava = Viiva();
}

void ViivaPankki::aloitaUusiKalibrointi() {
    kalibrointi = Viiva();
}

void ViivaPankki::lisaaPisteKalibrointiin(float x, float y, float paine) {
    kalibrointi.lisaaPiste(x,y,paine);
}

void ViivaPankki::lisaaPisteMuokattavaan(float x, float y, float paine) {
    muokattava.lisaaPiste(x,y,paine);
}

void ViivaPankki::tallennaHakemistoon(string polku) {

}

void ViivaPankki::lataaHakemistosta(string polku) {

}
