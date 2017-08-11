#include "Viiva.h"

ViivanPiste::ViivanPiste(float x_, float y_, float paine_) : x(x_), y(y_), paine(paine_) {
}

void Viiva::lisaaPiste(float x, float y, float paine) {
    pisteet.push_back(ViivanPiste(x, y, paine));

    //tahan tulee laskutoimitukset: tallennetaan juuri tehtyyn pisteeseen

}

ViivanOminaisuus::ViivanOminaisuus() : arvo(0), keskiarvo(0), keskihajonta(0), keskihajonnanKeskihajonta(0), konvergenssi(0) {
}

vector<float> Viiva::haeArvot(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> arvot;
    arvot.resize(ominaisuus->size(), 0);
    for (int i = 0; i < ominaisuus->size(); i++) {
        arvot[i] = (*ominaisuus)[i].arvo;
    }
    return arvot;
}

vector<float> Viiva::haeKeskiarvot(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskiarvot;
    keskiarvot.resize(ominaisuus->size(), 0);
    for (int i = 0; i < ominaisuus->size(); i++) {
        keskiarvot[i] = (*ominaisuus)[i].keskiarvo;
    }
    return keskiarvot;
}

vector<float> Viiva::haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskihajonnat;
    keskihajonnat.resize(ominaisuus->size(), 0);
    for (int i = 0; i < ominaisuus->size(); i++) {
        keskihajonnat[i] = (*ominaisuus)[i].keskihajonta;
    }
    return keskihajonnat;
}

vector<float> Viiva::haeKeskihajonnanKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> keskihajonnanKeskihajonnat;
    keskihajonnanKeskihajonnat.resize(ominaisuus->size(), 0);
    for (int i = 0; i < ominaisuus->size(); i++) {
        keskihajonnanKeskihajonnat[i] = (*ominaisuus)[i].keskihajonnanKeskihajonta;
    }
    return keskihajonnanKeskihajonnat;

}

vector<float> Viiva::haeKonvergenssit(vector<ViivanOminaisuus>* ominaisuus) {
    vector<float> konvergenssit;
    konvergenssit.resize(ominaisuus->size(), 0);
    for (int i = 0; i < ominaisuus->size(); i++) {
        konvergenssit[i] = (*ominaisuus)[i].konvergenssit;
    }
    return konvergenssit;

}