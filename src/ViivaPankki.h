#pragma once
#include "ofMain.h"
#include "Viiva.h"

/* ViivaPankki
 * Varasto-luokka viivoille.
 * ViivaPankki hllinnoi viivojen tallennusta ja latausta sekä 
 * uuden viivan pankkiin lisäämistä. Luokka pyrkii poistamaan tarpeen 
 * säilyttää Viiva tyyppisiä olioita tämän luokna ulkopuolella. ViivaPankki -luokassa
 * ei tapahdu laskemista. kts. ViivaOhjain
 */


struct ViivaPankki {

    vector<Viiva> viivat;

    // kalibrointi ja muokattava viiva pidetään erillään pankista. 
    // Näin pankki voidaan ladata ja tallentaa koska vain.
    Viiva kalibrointi;
    Viiva muokattava;
    
    // tällä hetkellä muokattava viiva lisätään viivat vectoriin
    void lisaaMuokattavaPankkiin();

    // nollausfunktiot kalibrointi ja muokattava Viivalle
    void aloitaUusiKalibrointi();
    void aloitaUusiMuokattava();
    
    // pisteen lisäysfunktiot kalibroinnille ja muokattavalle Viivalle
    void lisaaPisteKalibrointiin(float x, float y, float paine);
    void lisaaPisteMuokattavaan(float x, float y, float paine);
    
    
    // lataus ja tallennus
    // tapahtuu aina hakemistokohtaisesti.
    // tiedosto nimetään automaattisesti ajan mukaan
    void tallennaHakemistoon(string polku);
    void lataaHakemistosta(string polku);
    

};
