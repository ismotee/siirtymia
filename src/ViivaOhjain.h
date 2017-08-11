#pragma once
#include "ofMain.h"
#include "ViivaPankki.h"

struct ViivaOhjain {
    ViivaPankki pankki;
    string hakemisto;
        
    void setup(string hakemisto_);
    
    
    // Tarkastaa kalibroinnin laadukkuuden. Jos kalibrointi valmis, palauttaa true, muuten false
    bool kalibrointi(float x, float y, float paine);
    
    
private:
    //apufunktio kalibroinnille
    bool tarkastaKalibrointi();
};
