#pragma once
#include "ofMain.h"

struct ViivanPiste {
    float x,y,paine;
    ViivanPiste();
    ViivanPiste(float x_, float y_, float paine_);
};

struct ViivanOminaisuus {
    float arvo;
    float keskiarvo;
    float keskihajonta;
    float keskihajonnanKeskihajonta;
    float konvergenssi;
    ViivanOminaisuus();
    
};

struct Viiva {
    vector<ViivanPiste> pisteet;
    vector<ViivanOminaisuus> paksuus;
    vector<ViivanOminaisuus> sumeus;
    vector<ofColor> vari;

    void lisaaPiste(float x, float y, float paine);
    vector<float> haeArvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskiarvot(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKeskihajonnanKeskihajonnat(vector<ViivanOminaisuus>* ominaisuus);
    vector<float> haeKonvergenssit(vector<ViivanOminaisuus>* ominaisuus);
};
