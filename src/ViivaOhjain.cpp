#include "ViivaOhjain.h"
#include "tilastot.h"

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

    bool improvisaatioValmis = tarkastaImprovisaatio();

    if (improvisaatioValmis) {
        return true;
    }

    return false;
}

bool ViivaOhjain::laskeKohdeVari() {



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

void ViivaOhjain::aloitaImprovisointi() {
    pankki.kalibrointi = pankki.muokattava;

    samankaltaisuus.resize(pankki.viivat.size(), 0);
    improvisaatioLaskin = 0;
}

const Viiva& ViivaOhjain::etsiViiva() {

    ofVec2f kalibrointiVec = pankki.kalibrointi.paksuusSumeusVektori();
    ofVec2f muokattavaVec = pankki.muokattava.paksuusSumeusVektori();
    ofVec2f vertailuVec = (muokattavaVec - kalibrointiVec).getNormalized();
    float nearestValue = -100;
    int nearestId = -1;

    // lasketaan samankaltaisuus
    for (int i = 0; i < pankki.viivat.size(); i++) {

        ofVec2f vec = pankki.viivat[i].paksuusSumeusVektori();
        ofVec2f suunta = (vec - kalibrointiVec).getNormalized();

        samankaltaisuus[i] += suunta.dot(vertailuVec);
    }


    for (int i = 0; i < samankaltaisuus.size(); i++) {
        if (samankaltaisuus[i] > nearestValue) {
            nearestValue = samankaltaisuus[i];
            nearestId = i;
        }
    }

#ifdef VIIVA_DEBUG
    cout << "etsiViiva, nearestValue: " << nearestValue << "\n";
    cout << "etsiViiva, nearestId: " << nearestId << "\n";
#endif

    return pankki.viivat[nearestId];
}

float ViivaOhjain::muutoksenMaaraPolulla() {
    //lasketaan käyttäjän improvisoinninaikaisen eleen muutoksen projektio vektorilla, joka osoittaa lähtöpisteestä päämäärään, PS-koordinaatistossa.
    //skaalataan niin, että päämäärän kohdalla projektio on 1 ja lähtöpisteessä 0

    //eli muokattavan projektio samankaltaisimmalla
    ofVec2f m = pankki.muokattava.paksuusSumeusVektori();
    ofVec2f s = pankki.samankaltaisin.paksuusSumeusVektori();
    ofVec2f k = pankki.kalibrointi.paksuusSumeusVektori();

    float result = (m - k).dot((s - k).getNormalized()) / (s - k).length();

    result = ofClamp(result, -0.5, 1.2);
    //projektio on m . ŝ
    return result;
}

bool ViivaOhjain::tarkastaImprovisaatio() {

#ifdef VIIVA_DEBUG
    //cout << (pankki.muokattava.paksuusSumeusVektori() - pankki.kalibrointi.paksuusSumeusVektori()).length()<< "\n";
#endif


    if ((pankki.muokattava.paksuusSumeusVektori() - pankki.kalibrointi.paksuusSumeusVektori()).length() > 0.07) {
        improvisaatioLaskin++;
        pankki.samankaltaisin = etsiViiva();
    } else {
        samankaltaisuus.resize(pankki.viivat.size(), 0);
        improvisaatioLaskin = 0;
    }
    if (improvisaatioLaskin > 100) {
        return true;
    }

    return false;
}

bool ViivaOhjain::lahesty(ofPoint paikka, float paine) {
    pankki.muokattava.lisaaPiste(paikka, paine);
    lahestymisLaskuri++;

    muutos.push_back(ViivaOhjain::muutoksenMaaraPolulla());

    pankki.muokattava.muokkaaVaria2(pankki.samankaltaisin.vari, muutos.back());

    int start_i = muutos.size() - 150;
    if(start_i < 0) start_i = 0;
    
    vector<float> arvot;
    arvot.resize(muutos.size() - start_i, 0);

    cout << "start_i" << start_i << "\n";
    
    for (int i = start_i; i < muutos.size(); i++) {
        arvot[i - start_i] = muutos[i];
    }

    float muutoksenKeskihajonta = keskihajonta(arvot);
    cout << "muutoksen keskihajonta: " << muutoksenKeskihajonta << "\n";

    if (muutoksenKeskihajonta < 0.03 && lahestymisLaskuri > 150)
        return true;


    return false;
}
