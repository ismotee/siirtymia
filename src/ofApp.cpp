#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Ohjain::setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    Ohjain::update();
   // Vaiheet::verbose();
}

//--------------------------------------------------------------
void ofApp::draw(){
    Monitori::draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    Kyna::moved(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    Kyna::moved(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    Kyna::pressed(x,y);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    Kyna::released(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}