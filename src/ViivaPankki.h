#pragma once
#include "ofMain.h"
#include "Viiva.h"

struct ViivaPankki {

    vector<Viiva> viivat;
    Viiva kalibrointi;
    Viiva muokattava;
    
    void lisaaMuokattavaPankkiin();

    void aloitaUusiKalibrointi();
    void aloitaUusiMuokattava();
    
    void lisaaPisteKalibrointiin(float x, float y, float paine);
    void lisaaPisteMuokattavaan(float x, float y, float paine);
    
    
    
    void tallennaHakemistoon(string polku);
    void lataaHakemistosta(string polku);
    

};
