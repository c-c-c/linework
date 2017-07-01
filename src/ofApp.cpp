#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    savingPDF = false;
    drawMode = true;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // begins exporting as pdf
    if (savingPDF) {
    
        ofBeginSaveScreenAsPDF("screenPDF_"+ofGetTimestampString()+".pdf");
        }
    
    if (drawMode) {
        drawMode1();
        } else {
        drawMode2();
        }
    
    // ends exporting as pdf
    if (savingPDF) {
        ofEndSaveScreenAsPDF();
        savingPDF = false;
        }
    
}

//--------------------------------------------------------------
void ofApp::drawMode1() {
    
    
    ofSetBackgroundAuto(true); // disables background clearing
    ofBackground(255);
    float posX = ofGetMouseX();
    float posY = ofGetMouseY();
    
    for (auto point : drawnPoints){
        
        ofPoint mouse;
        mouse.set(posX, posY);
        float distance = (mouse - point).length();
        if (distance < 50){
            Line tempLine;
            tempLine.a = mouse;
            tempLine.b = point;
            lines.push_back(tempLine);
        }
    }
    drawnPoints.push_back(ofPoint(posX, posY));

    ofEnableAlphaBlending(); // enables transparency
    ofColor mauve(134, 83, 115, 30);
    ofColor army(75,83,32,30);
    ofSetColor(army);
    
    for (auto line : lines) {
        ofDrawLine(line.a, line.b);
    }
}

//--------------------------------------------------------------
void ofApp::drawMode2() {

    ofColor midnight(0, 51, 102);
    ofBackground(midnight);
    ofSetColor(255);
    
    trail.draw();
    
    float posX = ofGetMouseX();
    float posY = ofGetMouseY();
    
    ofPoint pt;
    pt.set(posX, posY);
    trail.addVertex(pt);
    
    
    }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // pressing the space bar erases everything by calling a method that clears the vectors' paths
    if (key == ' ') {
        drawnPoints.clear();
        lines.clear();
        trail.clear();
    }
    
    // by pressing 's' we use a method that exports the graphics on screen as PDF. Useful for keeping the work in vector-based format, to open in Illustrator for ex.
    if (key == 's') {
        savingPDF = true;
    }
    // by pressing 'c' we can export the graphics as a PNG for quick reference
    if (key == 'c') {
        ofImage screenshot;
        screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        screenshot.save("screenPNG_"+ ofGetTimestampString() + ".png");
    }
    
    // we alternate between the two drawing modes pressing either '1' or '2' on the keypad
    if (key == '1') {
        
        drawMode = true;
        cout << "drawing mode 1" << endl;
    }
    if (key == '2') {
        drawMode = false;
        cout << "drawing mode 2" << endl;
    }
        
 }
