#include "Ohjain.h"

void Ohjain::setup() {
    Vaiheet::setup();
}

VaiheetEnum Ohjain::kulje() {
    if(Kyna::click)
        return Kalibroi;
        
    return Kulje;
}

VaiheetEnum Ohjain::kalibroi() {
    if(!Kyna::drag)
        return Kulje;

    bool kalibrointiValmis;
    
    if(hidpen::isOpen)
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka.x,Kyna::paikka.y,Kyna::paine);
    else
        kalibrointiValmis = ViivaOhjain::kalibrointi(Kyna::paikka.x,Kyna::paikka.y,1);
    
    if(kalibrointiValmis)
        return Improvisoi;
    
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
