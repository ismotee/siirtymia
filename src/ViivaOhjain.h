#pragma once
#include "ofMain.h"
#include "ViivaPankki.h"

#define VIIVA_DEBUG



struct ViivaOhjain {
    ViivaPankki pankki;
    string hakemisto;
    vector<float> samankaltaisuus;
        
    void setup(string hakemisto_);
    void arvoMuokattavanVari();
    void tallennaKalibrointi();
    void aloitaImprovisointi();
    
    // Tarkastaa kalibroinnin laadukkuuden. Jos kalibrointi valmis, palauttaa true, muuten false
    bool kalibrointi(ofPoint paikka, float paine);
    bool improvisointi(ofPoint paikka, float paine);
    const Viiva& haeMuokattava() const;
    const Viiva& haeKalibrointi() const;
    
    const Viiva& etsiViiva();
    
    
private:
    //apufunktio kalibroinnille
    bool tarkastaKalibrointi();
    bool tarkastaImprovisaatio();
    
    int improvisaatioLaskin;
};
