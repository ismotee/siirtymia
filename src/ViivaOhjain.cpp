#include "ViivaOhjain.h"

void ViivaOhjain::setup(string hakemisto_) {
    hakemisto = hakemisto_;
    pankki.lataaHakemistosta(hakemisto);
}

bool ViivaOhjain::kalibrointi(ofPoint paikka, float paine) {

    pankki.lisaaPisteMuokattavaan(paikka, paine);

    if (tarkastaKalibrointi())
        pankki.lisaaPisteKalibrointiin(paikka, paine);
    else
        pankki.aloitaUusiKalibrointi();

    if (pankki.kalibrointi.pisteet.size() > 50)
        return true;

    return false;

}

bool ViivaOhjain::improvisointi(ofPoint paikka, float paine) {

    pankki.lisaaPisteMuokattavaan(paikka,paine);
    
    float sumeudenMuutos = pankki.muokattava.haeViimeisinSumeus().keskiarvo - pankki.kalibrointi.haeViimeisinSumeus().keskiarvo;
    float paksuudenMuutos = pankki.muokattava.haeViimeisinPaksuus().keskiarvo - pankki.kalibrointi.haeViimeisinPaksuus().keskiarvo;

    
}



bool ViivaOhjain::tarkastaKalibrointi() {
    float konvergenssi = pankki.muokattava.haeViimeisinPaksuus().konvergenssi * pankki.muokattava.haeViimeisinSumeus().konvergenssi;
    std::cout << "P: " << pankki.muokattava.haeViimeisinPaksuus().konvergenssi << " ";
    std::cout << "S: " << pankki.muokattava.haeViimeisinSumeus().konvergenssi << "\n";
    
    if (konvergenssi > 0.7)
        return true;
    return false;
}

const Viiva& ViivaOhjain::haeMuokattava() const {
        return pankki.muokattava;
}

const Viiva& ViivaOhjain::haeKalibrointi() const {
        return pankki.kalibrointi;
}

void ViivaOhjain::arvoMuokattavanVari() {
    pankki.muokattava.vari = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

void ViivaOhjain::tallennaKalibrointi() {
    pankki.lisaaMuokattavaPankkiin();
    pankki.tallennaHakemistoon(hakemisto);
}
