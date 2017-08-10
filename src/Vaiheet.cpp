#include "Vaiheet.h"

void Vaiheet::setup() {
    vaiheetEnum = Kulje;
    Kyna::setup();
}

void Vaiheet::update() {
    
    switch(vaiheetEnum) {
        case Kulje:
            vaiheetEnum = kulje();
            break;
        case Kalibroi:
            vaiheetEnum = kalibroi();
            break;
        case Improvisoi:
            vaiheetEnum = improvisoi();
            break;
        case LaskeKohde:
            vaiheetEnum = laskeKohde();
            break;
        case LahestyKohdetta:
            vaiheetEnum = lahestyKohdetta();
            break;
        case Viimeistele:
            vaiheetEnum = viimeistele();
            break;
        case Keskeyta:
            vaiheetEnum = keskeyta();
            break;
        default:
            vaiheetEnum = keskeyta();
            
            break;
        
    }
    
    //kyna::update vasta lopuksi koska muuten click boolean tyhjenee ennen kuin sitä on luettu
    Kyna::update();
}

void Vaiheet::verbose() {
    cout << vaiheetEnum << "\n";
}
