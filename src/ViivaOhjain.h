#pragma once
#include "ofMain.h"
#include "ViivaPankki.h"

struct ViivaOhjain {
    ViivaPankki pankki;
    string hakemisto;
        
    void setup(string hakemisto_);
    void arvoMuokattavanVari();
    void tallennaKalibrointi();
    
    // Tarkastaa kalibroinnin laadukkuuden. Jos kalibrointi valmis, palauttaa true, muuten false
    bool kalibrointi(ofPoint paikka, float paine);
    bool improvisointi(ofPoint paikka, float paine);
    const Viiva& haeMuokattava() const;
    const Viiva& haeKalibrointi() const;
    
    const Viiva& etsiViiva(ofVec2f vektori);
    
    
private:
    //apufunktio kalibroinnille
    bool tarkastaKalibrointi();
};
