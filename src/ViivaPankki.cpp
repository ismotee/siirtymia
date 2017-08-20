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
    tiedosto::tallennaViiva(muokattava,"./data/" +polku);
}

bool ViivaPankki::lataaHakemistosta(string polku) {
    ofDirectory dir(polku);
    if(!dir.exists()) {
        cout << "yritettiin ladata " << dir.getAbsolutePath() << "\n";
        return false;
    }   
        cout << "ladataan " << dir.getAbsolutePath() << "\n";
    
    dir.listDir();
    
    for(int i = 0; i < dir.size();i++)
        viivat.push_back(tiedosto::lataaViiva("./data/"+dir.getPath(i)));
    
}

void ViivaPankki::teeKalibraatioMuutos() {
    muokattava.muokkaaVaria(kalibrointi.haeViimeisinPaksuus(),kalibrointi.haeViimeisinSumeus());
}
