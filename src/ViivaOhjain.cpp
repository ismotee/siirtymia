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

    pankki.lisaaPisteMuokattavaan(paikka, paine);

    //laskee muokattavan ja kalibraation erotuksen ja lisää sen hsl:ään
    pankki.teeKalibraatioMuutos();

}

bool ViivaOhjain::tarkastaKalibrointi() {
    float konvergenssi = pankki.muokattava.haeViimeisinPaksuus().konvergenssi * pankki.muokattava.haeViimeisinSumeus().konvergenssi;

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
    pankki.muokattava.vari = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    pankki.muokattava.alkuperainenVari = pankki.muokattava.vari;
}

void ViivaOhjain::tallennaKalibrointi() {
    pankki.lisaaMuokattavaPankkiin();
    pankki.tallennaHakemistoon(hakemisto);
}

const Viiva& ViivaOhjain::etsiViiva() const {

    ofVec2f kalibrointiVec(pankki.kalibrointi.haeViimeisinPaksuus().keskiarvo,pankki.kalibrointi.haeViimeisinSumeus().keskiarvo);
    ofVec2f muokattavaVec(pankki.muokattava.haeViimeisinPaksuus().keskiarvo,pankki.muokattava.haeViimeisinSumeus().keskiarvo);
    ofVec2f vertailuVec = muokattavaVec - kalibrointiVec;
    float nearestValue = -1;
    int nearestId = -1;
    
    for (int i =0; i < pankki.viivat.size(); i++) {
        ofVec2f vec(pankki.viivat[i].haeViimeisinPaksuus().keskiarvo,pankki.viivat[i].haeViimeisinSumeus().keskiarvo);
        ofVec2f suunta = vec - kalibrointiVec;
        float dot = suunta.dot(vertailuVec);
        if(dot > nearestValue) {
            nearestValue = dot;
            nearestId = i;
        }
    }
    return pankki.viivat[nearestValue];
}
