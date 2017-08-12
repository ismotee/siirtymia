#include "Ohjain.h"

void Ohjain::setup() {
    Vaiheet::setup();
    Monitori::setup();
    
    //asetetaan viiva näkyväksi:
    Monitori::paljasta();
}


void Ohjain::update() {       
    /*tehdään update-asioita vaiheesta riippuen */
    Vaiheet::update();
    
    /*tehdään vaiheesta riippumattomat toimitukset:*/
    //piirretään viiva
    Monitori::piirraViiva(ViivaOhjain::haeMuokattava());
}


VaiheetEnum Ohjain::kulje() {
    //jos painetaan kynällä, aloitetaan kalibrointi
    if(Kyna::click)
        return Kalibroi;
    
    //muuten jatketaan tässä vaiheessa eikä näytetä mitään
    Monitori::tyhjenna();    
    return Kulje;
}


VaiheetEnum Ohjain::kalibroi() {
    //jos nostetaan kynä, kalibrointi keskeytetään ja palataan alkuun:
    if(!Kyna::drag)
        return Kulje;

    //onko kalibroitu onnistuneesti?
    bool kalibrointiValmis;
    
    //Kalibroidaan. Jos painekynä on käytössä, käytetään painedataa, muuten asetetaan paine=1
    if(hidpen::isOpen)
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka.x,Kyna::paikka.y,Kyna::paine);
    else
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka.x,Kyna::paikka.y,1);
    
    //Jos kalibrointi päättyi onnistuneesti, edetään seuraavaan vaiheeseen
    if(kalibrointiValmis)
        return Improvisoi;
    
    //Palautetaan seuraavana vaiheena VaiheetEnum Kalibroi, eli pysytään kalibrointivaiheessa
    return Kalibroi;
}


VaiheetEnum Ohjain::improvisoi() {
    return Improvisoi;
}

VaiheetEnum Ohjain::laskeKohde() {
    return LaskeKohde;
}

VaiheetEnum Ohjain::lahestyKohdetta() {
    return LahestyKohdetta;
}


VaiheetEnum Ohjain::viimeistele() {
    return Viimeistele;
}

VaiheetEnum Ohjain::keskeyta() {
    return Kulje;
}
