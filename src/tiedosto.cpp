#include "tiedosto.h"
#include <iterator>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

Viiva tiedosto::lataaViiva(std::string tiedostonNimi) {
    std::ifstream is(tiedostonNimi, ios::binary | ios::ate | ios::in);
    Viiva viiva;
    cout << "tiedoston nimi: " << tiedostonNimi << "\n";

    if (is.is_open()) {

        /*
        vector<ViivanPiste> pisteet;
        vector<ViivanOminaisuus> paksuus;
        vector<ViivanOminaisuus> sumeus;
        ofColor vari;
         */


        char* memory;

        //katsotaan koko tiedoston koko ja kelataan alkuun
        streampos size = is.tellg();
        is.seekg(0, ios::beg);
        cout << "tiedoston koko: " << size << "\n";

        // luetaan vektorin koko
        memory = new char[size];
        is.read(memory, size);
        int* vectorSize = (int*) memory;
                
        char* alkuKohta = sizeof (int) +memory;

        ofColor* col = (ofColor*) alkuKohta;
        viiva.vari = (*col);
        alkuKohta = alkuKohta + sizeof (ofColor);


        for (int i = 0; i < (*vectorSize); i++) {
            ViivanPiste* vp;
            vp = (ViivanPiste*) alkuKohta + (i * sizeof (ViivanPiste));
            viiva.pisteet.push_back((*vp));
        }

        alkuKohta = alkuKohta + ((*vectorSize) * sizeof (ViivanPiste));

        for (int i = 0; i < (*vectorSize); i++) {
            ViivanOminaisuus* paksuus;
            paksuus = (ViivanOminaisuus*) alkuKohta + (i * sizeof (ViivanOminaisuus));
            viiva.paksuus.push_back((*paksuus));
        }

        alkuKohta = alkuKohta + ((*vectorSize) * sizeof (ViivanOminaisuus));

        for (int i = 0; i < (*vectorSize); i++) {
            ViivanOminaisuus* sumeus;
            sumeus = (ViivanOminaisuus*) alkuKohta + (i * sizeof (ViivanOminaisuus));
            viiva.sumeus.push_back((*sumeus));
        }


        is.close();

        delete[] memory;
    }
    return viiva;
}

std::string tiedosto::aika() {
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_t);

}

void tiedosto::tallennaViiva(Viiva viiva, std::string polku) {
    std::string file = polku + aika() + ".ov";
    std::ofstream os(file, ios::binary);


    // kirjoitetaan koko. Pitäisi olla sama kaikilla vectoreilla

    char* buf;

    // tallennuksessa yritetään tallentaa juttuja siinä järjestyksessä, missä data olisi mahdollisimman vähän versioriippuvaista
    // esim viivan pisteet tuskin tallennetaan mitenkään muuten kuin ofPoint + paine datana
    // väri on aina olennainen joten se tallennetaan ensiksi.

    //vectorin koko ensin
    int size = viiva.pisteet.size();
    buf = (char*) &size;
    os.write(buf, sizeof (int));

    // sit väri
    buf = (char*) &viiva.vari;
    os.write(buf, sizeof (ofColor));

    //pisteet
    for (ViivanPiste& piste : viiva.pisteet) {
        char* buffer;
        buffer = (char*) &piste;
        os.write(buffer, sizeof (ViivanPiste));
    }


    //ViivanOminaisuudet
    for (ViivanOminaisuus& osaPaksuus : viiva.paksuus) {
        char* buffer;
        buffer = (char*) &osaPaksuus;
        os.write(buffer, sizeof (ViivanOminaisuus));
    }

    for (ViivanOminaisuus& osaSumeus : viiva.sumeus) {
        char* buffer;
        buffer = (char*) &osaSumeus;
        os.write(buffer, sizeof (ViivanOminaisuus));
    }


    os.close();
}

