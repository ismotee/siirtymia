#include "Ohjain.h"

void Ohjain::setup() {
    Vaiheet::setup();
    Monitori::setup();
    
    ViivaOhjain::setup("arkisto/");

    //asetetaan viiva näkyväksi:
    Monitori::paljasta();
    ViivaOhjain::pankki.aloitaUusiMuokattava();
    ViivaOhjain::pankki.aloitaUusiKalibrointi();
    ViivaOhjain::arvoMuokattavanVari();
}

void Ohjain::update() {
    /*tehdään update-asioita vaiheesta riippuen */
    Vaiheet::update();
    /*tehdään vaiheesta riippumattomat toimitukset:*/
    //piirretään viiva
    Monitori::piirraVari(ViivaOhjain::haeMuokattava().vari);
    Monitori::piirraViiva(ViivaOhjain::haeMuokattava());
}

VaiheetEnum Ohjain::kulje() {
    //jos painetaan kynällä, aloitetaan kalibrointi
    if (Kyna::click) {
        return Kalibroi;
    }
    //muuten jatketaan tässä vaiheessa eikä näytetä mitään
    return Kulje;
}

VaiheetEnum Ohjain::kalibroi() {
    //jos nostetaan kynä joksikin aikaa, kalibrointi keskeytetään ja palataan alkuun:
    static int irrotuslaskenta = 0;
    if (!Kyna::drag) {
        irrotuslaskenta++;
        if (irrotuslaskenta > 100) {
            irrotuslaskenta = 0;
            return Keskeyta;
        }
    } else
        irrotuslaskenta = 0;

    //onko kalibroitu onnistuneesti?
    bool kalibrointiValmis;

    //Kalibroidaan. Jos painekynä on käytössä, käytetään painedataa, muuten asetetaan paine=1
    if (hidpen::isOpen)
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka, Kyna::paine);
    else
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka, 1);

    //Jos kalibrointi päättyi onnistuneesti, edetään seuraavaan vaiheeseen
    if (kalibrointiValmis) {
        //tallenna viiva ja kuva
        ViivaOhjain::tallennaKalibrointi();
        Monitori::tallennaKuvana("kuvat/" + tiedosto::aika() + ".png");
        aloitaImprovisointi();
        return Improvisoi;
    }        

    //Palautetaan seuraavana vaiheena VaiheetEnum Kalibroi, eli pysytään kalibrointivaiheessa
    return Kalibroi;
}

VaiheetEnum Ohjain::improvisoi() {

    //jos nostetaan kynä joksikin aikaa, palataan alkuun. TODO: toimiiko tämä ihan oikein?
    static int irrotuslaskenta = 0;
    if (!Kyna::drag) {
        irrotuslaskenta++;
        if (irrotuslaskenta > 100) {
            irrotuslaskenta = 0;
            return Keskeyta;
        }
    } else
        irrotuslaskenta = 0;
    
    bool improvisointiValmis;
    
    if (hidpen::isOpen)
        improvisointiValmis = ViivaOhjain::improvisointi(Kyna::paikka, Kyna::paine);
    else
        improvisointiValmis = ViivaOhjain::improvisointi(Kyna::paikka, 1);        
    
    return Improvisoi;
}

VaiheetEnum Ohjain::laskeKohde() {
    return LaskeKohde;
}

VaiheetEnum Ohjain::lahestyKohdetta() {
    return LahestyKohdetta;
}

VaiheetEnum Ohjain::viimeistele() {
    
    //aloita UusiKalibrointi ja Muokattava
    ViivaOhjain::pankki.aloitaUusiKalibrointi();
    ViivaOhjain::pankki.aloitaUusiMuokattava();
    ViivaOhjain::arvoMuokattavanVari();    
    
    Monitori::tyhjenna();
    return Kulje;
}

VaiheetEnum Ohjain::keskeyta() {
    //tallennetaan kuva hylättävästä viivasta
    Monitori::tallennaKuvana("kuvat/hylätyt/" + tiedosto::aika() + ".png");
    
    Monitori::tyhjenna();
    ViivaOhjain::pankki.aloitaUusiMuokattava();
    ViivaOhjain::pankki.aloitaUusiKalibrointi();
    ViivaOhjain::arvoMuokattavanVari();
    return Kulje;
}
