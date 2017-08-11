#include "Viiva.h"
#include "tilastot.h"

ViivanPiste::ViivanPiste(float x_, float y_, float paine_) : x(x_), y(y_), paine(paine_), sijainti(ofPoint(x, y)) {
}

void Viiva::lisaaPiste(float x, float y, float paine) {
    //lisätään viivaan piste ja lasketaan sen ominaisuudet (sumeus, paksuus)

    //miten suurta osaa datasta käytetään tilastollisessa tarkastelussa:
    const int OTANNAN_KOKO = 100;

    //edellinen ja sitä edellinen piste: Jos ollaan lisäämässä ensimmäisiä pisteitä, käytetään default constructorin antamaa pistettä
    ViivanPiste viimePiste;
    ViivanPiste toissaPiste;
    if (!pisteet.empty())
        viimePiste = pisteet.back();
    if (pisteet.size() >= 2)
        toissaPiste = pisteet[pisteet.size() - 2];

    //lasketaan nopeus ja kiihtyvyys edellisten pisteiden sijainnin perusteella. Nopeus vektorina, kiihtyvyydestä riittää suuruus:
    ofPoint uusiSijainti(x, y);
    //ofPoint viimeSijainti(viimePiste.x, viimePiste.y);
    //ofPoint toissaSijainti(toissaPiste.x, toissaPiste.y);

    ofVec2f uusiNopeus = uusiSijainti - viimePiste.sijainti;
    ofVec2f viimeNopeus = viimePiste.sijainti - toissaPiste.sijainti;

    float kiihtyvyys = (uusiNopeus - viimeNopeus).length();

    //paksuus on kiihtyvyys
    ViivanOminaisuus uusiPaksuus;
    uusiPaksuus.arvo = kiihtyvyys;

    //lasketaan paksuuden keskiarvo ja keskihajonta
    std::vector<float> paksuudet;
    paksuudet = haeArvot(&paksuus, OTANNAN_KOKO);
    paksuudet.push_back(uusiPaksuus.arvo);
    uusiPaksuus.keskiarvo = keskiarvo(paksuudet);
    uusiPaksuus.keskihajonta = keskihajonta(paksuudet);

    //lasketaan paksuuden keskihajonnan keskihajonta
    std::vector<float> paksuudenHajonnat = haeKeskihajonnat(&paksuus, OTANNAN_KOKO);
    paksuudenHajonnat.push_back(uusiPaksuus.keskihajonta);
    uusiPaksuus.keskihajonnanKeskihajonta = keskihajonta(paksuudenHajonnat);

    //paksuuden konvergenssi eli ovatko viivan laadut vakiintuneet.
    //Konvergenssi on luokkaa -inf...1 Kun konvergenssi on luokkaa 0.6...1, voidaan laatujen tulkita vakiintuneen
    uusiPaksuus.konvergenssi = 1 - 5 * uusiPaksuus.keskihajonnanKeskihajonta / uusiPaksuus.keskiarvo;


    //sumeus on paineen vastakohta
    ViivanOminaisuus uusiSumeus;
    uusiSumeus.arvo = 1 - paine;

    //lasketaan sumeuden keskiarvo ja keskihajonta
    std::vector<float> sumeudet = haeArvot(&sumeus, OTANNAN_KOKO);
    sumeudet.push_back(uusiSumeus.arvo);
    uusiSumeus.keskiarvo = keskiarvo(sumeudet);
    uusiSumeus.keskihajonta = keskihajonta(sumeudet);

    //lasketaan sumeuden keskihajonnan keskihajonta
    std::vector<float> sumeudenHajonnat = haeKeskihajonnat(&sumeus, OTANNAN_KOKO);
    sumeudenHajonnat.push_back(uusiSumeus.keskihajonta);
    uusiSumeus.keskihajonnanKeskihajonta = keskihajonta(sumeudenHajonnat);

    //sumeuden konvergenssi -- huom. tämä ei riipu suuruudesta kuten paksuuden konvergenssi, sillä sumeuden mittakaava on aina sama 0...1
    uusiSumeus.konvergenssi = 1 - 5 * uusiSumeus.keskihajonnanKeskihajonta;

    //lisätään piste ja ominaisuudet viivaan
    pisteet.push_back(ViivanPiste(x, y, paine));
    paksuus.push_back(uusiPaksuus);
    sumeus.push_back(uusiSumeus);
}

ViivanOminaisuus::ViivanOminaisuus() : arvo(0), keskiarvo(0), keskihajonta(0), keskihajonnanKeskihajonta(0), konvergenssi(0) {
}

vector<float> Viiva::haeArvot(vector<ViivanOminaisuus>* ominaisuus) {
    //tarkistetaan että osoite on validi
    if (ominaisuus != &paksuus || ominaisuus != &sumeus)
        return vector<float>(0);

    vector<float> arvot;
    arvot.resize(ominaisuus->size(), 0);
    for (unsigned int i = 0; i < ominaisuus->size(); i++) {
        arvot[i] = (*ominaisuus)[i].arvo;
    }
    return arvot;
}

vector<float> Viiva::haeArvot(vector<ViivanOminaisuus>* ominaisuus, unsigned int otanta) {
    //tarkistetaan että osoite on validi
    if (ominaisuus != &paksuus && ominaisuus != &sumeus)
        return vector<float>(0);


    //lasketaan montako jäsentä oikeasti palautetaan = n    
    vector<float> arvot;
    int n;
    if (otanta >= ominaisuus->size())
        n = ominaisuus->size();
    else if (otanta <= 0)
        return vector<float>(0);
    else
        n = otanta;

    //kopioidaan arvot ominaisuudesta    
    arvot.resize(n);
    unsigned int start_i = ominaisuus->size() - n;
    for (unsigned int i = start_i; i < ominaisuus->size(); i++) {
        arvot[i-start_i] = (*ominaisuus)[i].arvo;
    }
    return arvot;
}

vector<float> Viiva::haeKeskiarvot(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskiarvot;
    keskiarvot.resize(ominaisuus->size(), 0);
    for (unsigned int i = 0; i < ominaisuus->size(); i++) {
        keskiarvot[i] = (*ominaisuus)[i].keskiarvo;
    }
    return keskiarvot;
}

vector<float> Viiva::haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskihajonnat;
    keskihajonnat.resize(ominaisuus->size(), 0);
    for (unsigned int i = 0; i < ominaisuus->size(); i++) {
        keskihajonnat[i] = (*ominaisuus)[i].keskihajonta;
    }
    return keskihajonnat;
}

vector<float> Viiva::haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus, unsigned int otanta) {
    //tarkistetaan että osoite on validi. Jos ei, palautetaan tyhjä vektori
    if (ominaisuus != &paksuus && ominaisuus != &sumeus)
        return vector<float>(0);

    //lasketaan montako jäsentä oikeasti palautetaan = n
    vector<float> keskihajonnat;
    int n;
    if (otanta >= ominaisuus->size())
        n = ominaisuus->size();
    else if (otanta <= 0)
        return vector<float>(0);
    else
        n = otanta;

    //kopioidaan arvot ominaisuudesta
    keskihajonnat.resize(n);
    unsigned int start_i = ominaisuus->size() - n;
    for (unsigned int i = start_i; i < ominaisuus->size(); i++)
        keskihajonnat[i-start_i] = (*ominaisuus)[i].keskihajonta;

    return keskihajonnat;
}

vector<float> Viiva::haeKeskihajonnanKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskihajonnanKeskihajonnat;
    keskihajonnanKeskihajonnat.resize(ominaisuus->size(), 0);
    for (unsigned int i = 0; i < ominaisuus->size(); i++) {
        keskihajonnanKeskihajonnat[i] = (*ominaisuus)[i].keskihajonnanKeskihajonta;
    }
    return keskihajonnanKeskihajonnat;

}

vector<float> Viiva::haeKonvergenssit(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> konvergenssit;
    konvergenssit.resize(ominaisuus->size(), 0);
    for (unsigned int i = 0; i < ominaisuus->size(); i++) {
        konvergenssit[i] = (*ominaisuus)[i].konvergenssi;
    }
    return konvergenssit;

}

ViivanPiste Viiva::haeViimeisinPiste() {
    if (!pisteet.empty())
        return pisteet.back();
    //TODO: keksi parempi ratkaisu
    return ViivanPiste();
}

ViivanOminaisuus Viiva::haeViimeisinPaksuus() {
    if (!paksuus.empty())
        return paksuus.back();
    return ViivanOminaisuus();
}

ViivanOminaisuus Viiva::haeViimeisinSumeus() {
    if (!sumeus.empty())
        return sumeus.back();
    return ViivanOminaisuus();
}

