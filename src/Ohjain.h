#pragma once
#include "ofMain.h"
#include "Vaiheet.h"
#include "ViivaOhjain.h"
#include "Monitori.h"
#include "OscInterface.h"

struct Ohjain: public Vaiheet, public ViivaOhjain, public Monitori, public OscInterface {

    void setup();
    void update();
    
    bool tallennetaan = false;

    VaiheetEnum improvisoi();

    VaiheetEnum kalibroi();
    
    VaiheetEnum keskeyta();

    VaiheetEnum kulje();

    VaiheetEnum lahestyKohdetta();

    VaiheetEnum laskeKohde();

    VaiheetEnum viimeistele();
    
};
