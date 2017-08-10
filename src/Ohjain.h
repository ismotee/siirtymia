#pragma once
#include "ofMain.h"
#include "Vaiheet.h"

struct Ohjain: public Vaiheet {

    void setup();


    VaiheetEnum improvisoi();

    VaiheetEnum kalibroi();
    
    VaiheetEnum keskeyta();

    VaiheetEnum kulje();

    VaiheetEnum lahestyKohdetta();

    VaiheetEnum laskeKohde();

    VaiheetEnum viimeistele();
    
};
