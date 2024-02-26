#pragma once

#include "ofMain.h"
#include "Turing.hpp"
#include "ofxPd.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);
    
    float boxSize = 50;
    int gWidth = 46;
    int gHeight = 22;
    float y_off = 0;
    
    ofFbo turingCanvas;
    ofFbo golCanvas;
    ofRectangle turingRect;
    
    ofImage img;
    
    Turing turing;
    
    ofRectangle getRect(int x, int y, int w, int h);
    
    //GOL
    const int x_resolution = 26;
    const int y_resolution = 36;
    vector<vector<bool>> cells;
    vector<vector<bool>> cells_last;
    void updateGOL(int speed);
    bool golPaused = false;
    ofRectangle golRect;
    unsigned long lastGOLUpdate = 0;
    unsigned long pause_time = 0;
    
    ofxPd pd;
    
    ofTrueTypeFont font;
};
