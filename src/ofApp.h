#pragma once

#include "ofMain.h"

class Line { // we will pass this class into the vector drawnPoints
public:
    ofPoint a; // point where line begins
    ofPoint b; // point where line ends
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
        void drawMode1(); // drawing mode 1
        void drawMode2(); // drawing mode 2

		void keyPressed(int key); // contains event handlers to clear screen, export graphics and alternate between drawing modes
    
    // for drawing mode 1
    vector < ofPoint > drawnPoints;
    vector < Line > lines;
    
    ofPolyline trail;
    
    bool savingPDF; // to save the sketch in a vector format
    
    bool drawMode; // to alternate between 2 drawing modes

    
};
