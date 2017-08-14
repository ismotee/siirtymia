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

void ViivaPankki::lisaaPisteKalibrointiin(ofPoint paikka, float paine) {
    kalibrointi.lisaaPiste(paikka,paine);
}

void ViivaPankki::lisaaPisteMuokattavaan(ofPoint paikka, float paine) {
    muokattava.lisaaPiste(paikka,paine);
}

void ViivaPankki::tallennaHakemistoon(string polku) {
    tiedosto::tallennaViiva(muokattava,"./bin/data/" +polku);
}

void ViivaPankki::lataaHakemistosta(string polku) {
    ofDirectory dir(polku);
    dir.listDir();

    for(int i = 0; i < dir.size();i++)
        viivat.push_back(tiedosto::lataaViiva(dir.getPath(i)));
    
}
