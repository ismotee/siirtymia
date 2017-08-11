#pragma once
#include "ofMain.h"
#include "Vaiheet.h"
#include "ViivaOhjain.h"

struct Ohjain: public Vaiheet, public ViivaOhjain {

    void setup();


    VaiheetEnum improvisoi();

    VaiheetEnum kalibroi();
    
    VaiheetEnum keskeyta();

    VaiheetEnum kulje();

    VaiheetEnum lahestyKohdetta();

    VaiheetEnum laskeKohde();

    VaiheetEnum viimeistele();
    
};
