#include "Kyna.h"

void Kyna::setup() {
    hidpen::setup("./bin/hidpenSettings");
//    hidpen::setup(0);
    paine = 0;
    paikka = ofPoint();
}

void Kyna::update() {
    click = false;

    if(hidpen::isOpen) {
        hidpen::update();
        paine = hidpen::pressure;
    }
}

void Kyna::pressed(float x, float y) {
    paikka = ofPoint(x, y);
    click = true;
    drag = true;
}

void Kyna::moved(float x, float y) {
    paikka = ofPoint(x, y);
}

void Kyna::released(float x, float y) {
    paikka = ofPoint(x, y);
    drag = false;
}



