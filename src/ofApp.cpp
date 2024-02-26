#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    #ifdef TARGET_OSX
    ofSetWindowShape(1920 *.5, 1080 * .5);
    #endif
    boxSize = ofGetWidth() / (gWidth + 2);
    y_off = (ofGetHeight() - boxSize * gHeight) / 2;
    
    font.load("Andale Mono.ttf", 12);
    
    ofDisableAntiAliasing();
    
    turing.init(13*boxSize, 13, 13);
    turingRect = getRect(5, 2, 13, 13);
    turing.zone = turingRect;
    
    golCanvas.allocate(13*boxSize, 18*boxSize);
    golRect = getRect(28, 2, 13, 18);
    
    turing.setStatePos(getRect(5, 16, 2, 4), 0, 0);
    turing.setStatePos(getRect(8, 16, 2, 4), 1, 1);
    turing.setStatePos(getRect(13, 16, 2, 4), 2, 0);
    turing.setStatePos(getRect(16, 16, 2, 4), 3, 1);
    
    //Init gol
    for(int x = 0; x < x_resolution; x++){
        vector<bool> row;
        for(int y = 0; y < y_resolution; y++){
            row.push_back(ofRandom(100) < 10);
        }
        cells.push_back(row);
        cells_last.push_back(row);
    }
    
    
    golPaused = false;
    
    
    // setup OF sound stream
    ofSoundStreamSettings settings;
    settings.numInputChannels = 0;
    settings.numOutputChannels = 2;
    settings.sampleRate = 44100;
    settings.bufferSize = ofxPd::blockSize() * 8;
    settings.setInListener(this);
    settings.setOutListener(this);
    ofSoundStreamSetup(settings);
    
    if(!pd.init(2, 0, 44100, 8, false)) {
        OF_EXIT_APP(1);
    }
    
    pd.start();
    
    pd::Patch patch = pd.openPatch("audio/turing_gol.pd");
}

//--------------------------------------------------------------
void ofApp::update(){
    turing.update(125);
    
    updateGOL(125);
    
    golCanvas.begin();
    ofBackground(0, 50);
    float box_size = float(golCanvas.getWidth()) / float(x_resolution);
    for(int x = 0; x < x_resolution; x++){
        for(int y = 0; y < y_resolution; y++){
            ofNoFill();
            ofSetColor(255, 100);
            ofDrawRectangle(
                          ofMap(x, 0, x_resolution, 0, golCanvas.getWidth()),
                          ofMap(y, 0, y_resolution, 0, golCanvas.getHeight()),
                            golCanvas.getWidth()/x_resolution,
                            golCanvas.getHeight()/y_resolution);
            ofFill();
            if(cells[x][y]){
                ofSetColor(255);
                ofDrawRectangle(
                              ofMap(x, 0, x_resolution, 0, golCanvas.getWidth()),
                              ofMap(y, 0, y_resolution, 0, golCanvas.getHeight()),
                                golCanvas.getWidth()/x_resolution,
                                golCanvas.getHeight()/y_resolution);
            }
        }
    }
    
    
    
    golCanvas.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255,50);
    ofNoFill();
    for(int x = 0; x < gWidth; x++){
        for(int y = 0; y < gHeight; y++){
            ofDrawRectangle(getRect(x, y, 1, 1));
        }
    }
    
    ofSetColor(255);
    ofDrawRectangle(turingRect);
    ofDrawRectangle(golRect);
    
    ofFill();
    ofSetColor(255,200);
    turing.drawCanvas(turingRect.x, turingRect.y);
    turing.drawUi();
    
    ofSetColor(255, 0, 0);
//    ofDrawEllipse(turing.readPos.x + turingRect.x, turing.readPos.y + turingRect.y, 5, 5);
    
    ofSetColor(255);
    golCanvas.draw(golRect);
    
    ofRectangle rr = getRect(5, 1, 5, 5);
    font.drawString("Turing Machine",rr.x, rr.y);
    rr = getRect(28, 1, 5, 5);
    font.drawString("Conways Game of Life",rr.x, rr.y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'x'){
            img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
            img.save("screenshot.png");
        }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(golRect.inside(x, y)){
        int grid_x = ofMap(x - golRect.x, 0, golCanvas.getWidth(), 0, x_resolution);
        int grid_y = ofMap(y - golRect.y, 0, golCanvas.getHeight(), 0, y_resolution);
        cells[grid_x][grid_y] = true;
        cells_last[grid_x][grid_y] = true;
        pause_time = ofGetSystemTimeMillis();
        golPaused = true;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    turing.press(x, y);
    if(golRect.inside(x, y)){
        int grid_x = ofMap(x - golRect.x, 0, golCanvas.getWidth(), 0, x_resolution);
        int grid_y = ofMap(y - golRect.y, 0, golCanvas.getHeight(), 0, y_resolution);
        cells[grid_x][grid_y] = true;
        cells_last[grid_x][grid_y] = true;
        pause_time = ofGetSystemTimeMillis();
        golPaused = true;
        
        int index = grid_x + grid_y * x_resolution;
        pd.sendFloat("fx_2", grid_y);
        cout << "index: " << grid_y << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    golPaused = false;
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


ofRectangle ofApp::getRect(int x, int y, int w, int h){
    return ofRectangle(boxSize + x * boxSize, y_off + y * boxSize, w * boxSize, h * boxSize);
}

void ofApp::updateGOL(int speed){
    if(ofGetSystemTimeMillis() - lastGOLUpdate < speed){
        return;
    }
    lastGOLUpdate = ofGetSystemTimeMillis();
    if(!golPaused && ofGetSystemTimeMillis() - pause_time > 1000){
        for(int x = 0; x < x_resolution; x++){
            for(int y = 0; y < y_resolution; y++){
                int index = x + y * x_resolution;
                int alive = 0;
                for(int c = -1; c < 2; c++)
                {
                    for(int d = -1; d < 2; d++)
                    {
                        
                        if(x+c < 0 || x+c >= x_resolution || y+d < 0 || y+d >= y_resolution)
                        {
                            continue;
                        }
                        
                        if(!(c == 0 && d == 0))
                        {
                            if(cells_last[x+c][y+d])
                            {
                                ++alive;
                            }
                        }
                    }
                }
                if(alive < 2)
                {
                    cells[x][y] = false;
                }
                else if(alive == 3)
                {
                    cells[x][y] = true;
                }
                else if(alive > 3)
                {
                    cells[x][y] = false;
                }
            }
        }
        
        for(int x = 0; x < x_resolution; x++){
            for(int y = 0; y < y_resolution; y++){
                cells_last[x][y] = cells[x][y];
            }
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
}
