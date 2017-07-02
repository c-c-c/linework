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
    
    //  now we are taking the current position of our mouse we are comparing it with all its previous position.
    
    for (auto point : drawnPoints){
        
        ofPoint mouse;
        mouse.set(posX, posY);
    
    // if the distance between the current position of our mouse and a previous position is less than a certain number (here 50 pixels), we create a Line tempLine that connects the position of the mouse with the point in the history vector drawnPoints which distance is less than 50px.
        float distance = (mouse - point).length();
        if (distance < 50){
            Line tempLine;
            tempLine.a = mouse;
            tempLine.b = point;
    // now we push the tempLine in the lines vector, ready do be drawned on screen.
            lines.push_back(tempLine);
        }
    }
    // everytime we move the mouse, we're saving the position of the mouse in the
    // drawnPoints vector. the method push_back adds the position at the end of the vector.
    // that vector holds all of movements of our mouse on the screen.
    drawnPoints.push_back(ofPoint(posX, posY));

    ofEnableAlphaBlending(); // enables transparency
    ofColor mauve(134, 83, 115, 30);
    ofColor army(75,83,32,30);
    ofSetColor(army);
    
    // we use ofDrawLine to connect points a and b from the Lines class that we created
    // in the header by drawing a line between each point
    for (auto line : lines) {
        ofDrawLine(line.a, line.b);
    }
}

//--------------------------------------------------------------
void ofApp::drawMode2() {

    // drawing mode 2 makes use of the Polyline class to create a trail of points. Each point corresponds to the position of our mouse at a given time. It's a pretty loose drawing tool, that can be nice to have to do things like line-drawing portraits. 
    
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
