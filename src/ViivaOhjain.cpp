#include "ViivaOhjain.h"

void ViivaOhjain::setup(string hakemisto_) {
    hakemisto = hakemisto_;
    //pankki.lataaHakemistosta(hakemisto);
}

bool ViivaOhjain::kalibrointi(ofPoint paikka, float paine) {

    pankki.lisaaPisteMuokattavaan(paikka, paine);

    if (tarkastaKalibrointi())
        pankki.lisaaPisteKalibrointiin(paikka, paine);
    else
        pankki.aloitaUusiKalibrointi();

    if (pankki.kalibrointi.pisteet.size() >= Viiva::OTANNAN_KOKO)
        return true;

    return false;

}

bool ViivaOhjain::tarkastaKalibrointi() {
float konvergenssi = pankki.muokattava.haeViimeisinPaksuus().konvergenssi * pankki.muokattava.haeViimeisinSumeus().konvergenssi;
    
    if (konvergenssi > 0.8)
        return true;
    return false;
}

const Viiva& ViivaOhjain::haeMuokattava() const {
        return pankki.muokattava;
}

const Viiva& ViivaOhjain::haeKalibrointi() const {
        return pankki.kalibrointi;
}

