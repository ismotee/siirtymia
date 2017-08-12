#include "ViivaOhjain.h"

void ViivaOhjain::setup(string hakemisto_) {
    hakemisto = hakemisto_;
    //pankki.lataaHakemistosta(hakemisto);
}

bool ViivaOhjain::kalibrointi(float x, float y, float paine) {

    pankki.lisaaPisteMuokattavaan(x, y, paine);

    if (tarkastaKalibrointi())
        pankki.lisaaPisteKalibrointiin(x, y, paine);
    else
        pankki.aloitaUusiKalibrointi();

    if (pankki.kalibrointi.pisteet.size() > 200)
        return true;

    return false;

}

bool ViivaOhjain::tarkastaKalibrointi() {

    if (pankki.muokattava.haeViimeisinPaksuus().konvergenssi < 0.2)
        return true;
    return false;
}

Viiva ViivaOhjain::haeMuokattava() {
    if (!pankki.muokattava.pisteet.empty())
        return pankki.muokattava;
    return Viiva();
}

Viiva ViivaOhjain::haeKalibrointi() {
    if(!pankki.kalibrointi.pisteet.empty())
        return pankki.kalibrointi;
    return Viiva();
}

