//
//  Turing.hpp
//  AI-turing_gol
//
//  Created by Max Björverud on 2024-02-19.
//

#ifndef Turing_hpp
#define Turing_hpp

#include "ofMain.h"

class TuringState {
public:
    TuringState(){
        pil_h.load("pil_h.png");
        pil_v.load("pil_v.png");
    }
    ~TuringState(){};
    
    void setTrue(int _next, int _dir, int _set){
        readTrue.clear();
        readTrue.push_back(_next);
        readTrue.push_back(_dir);
        readTrue.push_back(_set);
    }
    void setFalse(int _next, int _dir, int _set){
        readFalse.clear();
        readFalse.push_back(_next);
        readFalse.push_back(_dir);
        readFalse.push_back(_set);
    }
    
    vector<int> update(bool readState){
        if(readState){
            return readTrue;
        }else{
            return readFalse;
        }
    }
    
    void drawUi(ofColor clr){
        ofSetColor(clr);
        ofNoFill();
        ofDrawRectangle(squareStateUi);
        ofDrawRectangle(ellipseStateUi);
        ofFill();
        ofSetColor(255);
        ofDrawRectangle(squareStateUi.x + squareStateUi.width/4, squareStateUi.y + squareStateUi.width/4, squareStateUi.width/2, squareStateUi.width/2);
       
        
        //Draw set
        if(readTrue[2] == 1){
            ofDrawRectangle(
                            squareStateUi.x + squareStateUi.width/4,
                            squareStateUi.y + squareStateUi.height * .25 + squareStateUi.width/4,
                            squareStateUi.width/2,
                            squareStateUi.width/2);
        }else if(readTrue[2] == 0){
            ofDrawEllipse(squareStateUi.x + squareStateUi.width/2,
                          squareStateUi.y + squareStateUi.height * .25 + squareStateUi.width/2,
                          squareStateUi.width/2,
                          squareStateUi.width/2);

        }else{
            ofDrawLine(squareStateUi.x,
                       squareStateUi.y + squareStateUi.height * .25,
                       squareStateUi.x + squareStateUi.width,
                       squareStateUi.y + squareStateUi.height * .5);
            
            ofDrawLine(squareStateUi.x + squareStateUi.width,
                       squareStateUi.y + squareStateUi.height * .25,
                       squareStateUi.x,
                       squareStateUi.y + squareStateUi.height * .5);
        }
        
        if(readTrue[1] == -1){
            pil_v.draw(squareStateUi.x + squareStateUi.width/4, squareStateUi.y + squareStateUi.height * .75 + squareStateUi.width/4, squareStateUi.width/2, squareStateUi.width/2);
        }else{
            pil_h.draw(squareStateUi.x + squareStateUi.width/4, squareStateUi.y + squareStateUi.height * .75 + squareStateUi.width/4, squareStateUi.width/2, squareStateUi.width/2);
        }
        ofFill();
        if(readTrue[0] == 0){
            ofSetColor(ofColor::red);
        }else if(readTrue[0] == 1){
            ofSetColor(ofColor::green);
        }else if(readTrue[0] == 2){
            ofSetColor(ofColor::blue);
        }else if(readTrue[0] == 3){
            ofSetColor(ofColor::purple);
        }
        ofDrawRectangle(squareStateUi.x + squareStateUi.width/4, squareStateUi.y + squareStateUi.height * .5 + squareStateUi.width/4, squareStateUi.width/2, squareStateUi.width/2);
        
        ofSetColor(255);
        
        //False read
        ofDrawEllipse(ellipseStateUi.x + ellipseStateUi.width/2, ellipseStateUi.y + squareStateUi.width/2, ellipseStateUi.width/2, ellipseStateUi.width/2);
        
        if(readFalse[2] == 1){
            ofDrawRectangle(
                            ellipseStateUi.x + ellipseStateUi.width/4,
                            ellipseStateUi.y + ellipseStateUi.height * .25 + ellipseStateUi.width/4,
                            ellipseStateUi.width/2,
                            ellipseStateUi.width/2);
        }else if(readFalse[2] == 0){
            ofDrawEllipse(ellipseStateUi.x + ellipseStateUi.width/2,
                          ellipseStateUi.y + ellipseStateUi.height * .25 + ellipseStateUi.width/2,
                          ellipseStateUi.width/2,
                          ellipseStateUi.width/2);

        }else{
            ofDrawLine(ellipseStateUi.x,
                       ellipseStateUi.y + ellipseStateUi.height * .25,
                       ellipseStateUi.x + ellipseStateUi.width,
                       ellipseStateUi.y + ellipseStateUi.height * .5);
            
            ofDrawLine(ellipseStateUi.x + ellipseStateUi.width,
                       ellipseStateUi.y + squareStateUi.height * .25,
                       ellipseStateUi.x,
                       ellipseStateUi.y + ellipseStateUi.height * .5);
        }
        
        if(readFalse[1] == -1){
            pil_v.draw(ellipseStateUi.x + ellipseStateUi.width/4, ellipseStateUi.y + ellipseStateUi.height * .75 + ellipseStateUi.width/4, ellipseStateUi.width/2, ellipseStateUi.width/2);
        }else{
            pil_h.draw(ellipseStateUi.x + ellipseStateUi.width/4, ellipseStateUi.y + ellipseStateUi.height * .75 + ellipseStateUi.width/4, ellipseStateUi.width/2, ellipseStateUi.width/2);
        }
        
        ofFill();
        if(readFalse[0] == 0){
            ofSetColor(ofColor::red);
        }else if(readFalse[0] == 1){
            ofSetColor(ofColor::green);
        }else if(readFalse[0] == 2){
            ofSetColor(ofColor::blue);
        }else if(readFalse[0] == 3){
            ofSetColor(ofColor::purple);
        }
        ofDrawRectangle(ellipseStateUi.x + ellipseStateUi.width/4, ellipseStateUi.y + ellipseStateUi.height * .5 + ellipseStateUi.width/4, ellipseStateUi.width/2, ellipseStateUi.width/2);
        
        
        
        //MARK INDEX
        switch (markIndex) {
            case 0:
                markPoint.set(squareStateUi.x + squareStateUi.width/2, squareStateUi.y + squareStateUi.width/2);
                break;
            case 1:
                markPoint.set(squareStateUi.x + squareStateUi.width/2, squareStateUi.y + squareStateUi.height * .25 + squareStateUi.width/2);
                break;
            case 2:
                markPoint.set(squareStateUi.x + squareStateUi.width/2, squareStateUi.y + squareStateUi.height * .5 + squareStateUi.width/2);
                break;
            case 3:
                markPoint.set(squareStateUi.x + squareStateUi.width/2, squareStateUi.y + squareStateUi.height * .75 + squareStateUi.width/2);
                break;
            
            case 4:
                markPoint.set(ellipseStateUi.x + ellipseStateUi.width/2, ellipseStateUi.y + ellipseStateUi.width/2);
                break;
            case 5:
                markPoint.set(ellipseStateUi.x + ellipseStateUi.width/2, ellipseStateUi.y + ellipseStateUi.height * .25 + ellipseStateUi.width/2);
                break;
            case 6:
                markPoint.set(ellipseStateUi.x + ellipseStateUi.width/2, ellipseStateUi.y + ellipseStateUi.height * .5 + ellipseStateUi.width/2);
                break;
            case 7:
                markPoint.set(ellipseStateUi.x + ellipseStateUi.width/2, ellipseStateUi.y + ellipseStateUi.height * .75 + ellipseStateUi.width/2);
                break;
                
            default:
                break;
        }
        ofFill();
        ofSetColor(255);
        ofDrawEllipse(markPoint, ellipseStateUi.width/4, ellipseStateUi.width/4);
    };
    
    void press(int x, int y){
        //Read true == square
        if(squareStateUi.inside(x, y)){
            int selector = ofMap(y, squareStateUi.y, squareStateUi.y + squareStateUi.height, 0, 4);
            switch (selector) {
                case 1:
                    readTrue[2] ++;
                    readTrue[2] %= 3;
                    break;
                case 3:
                    if(readTrue[1] == -1){
                        readTrue[1] = 1;
                    }else{
                        readTrue[1] = -1;
                    }
                    break;
                case 2:
                    readTrue[0]++;
                    readTrue[0] %= 4;
                    break;
                default:
                    break;
            }
        }else if(ellipseStateUi.inside(x, y)){
            int selector = ofMap(y, ellipseStateUi.y, ellipseStateUi.y + ellipseStateUi.height, 0, 4);
            switch (selector) {
                case 1:
                    readFalse[2] ++;
                    readFalse[2] %= 3;
                    break;
                case 3:
                    if(readFalse[1] == -1){
                        readFalse[1] = 1;
                    }else{
                        readFalse[1] = -1;
                    }
                    break;
                case 2:
                    readFalse[0]++;
                    readFalse[0] %= 4;
                    break;
                default:
                    break;
            }
            
        }
    };
    
    void setUi(ofRectangle rec, int _in){
        pos.x = rec.x;
        pos.y = rec.y;
        squareStateUi.x = rec.x;
        squareStateUi.y = rec.y;
        squareStateUi.width = rec.width * .5;
        squareStateUi.height = rec.height;
        
        ellipseStateUi.x = rec.x + rec.width * .5;
        ellipseStateUi.y = rec.y;
        ellipseStateUi.width = rec.width * .5;
        ellipseStateUi.height = rec.height;
        
        in_dir = _in;
    };
    
    void mark(int index){
        markIndex = index;
    }
    
    ofPolyline getStartLine(){
        ofPolyline pline;
        if(in_dir == 0){
            pline.addVertex(markPoint.x, markPoint.y);
            pline.addVertex(pos.x - squareStateUi.width,markPoint.y);
        }else{
            pline.addVertex(markPoint.x, markPoint.y);
            pline.addVertex(ellipseStateUi.x + ellipseStateUi.width*2,markPoint.y);
        }
        return pline;
    }
    
    ofVec2f pos;
    int in_dir = 0;
    int markIndex = -1;
    
private:
    vector<int> readTrue;
    vector<int> readFalse;
        
    ofImage pil_h;
    ofImage pil_v;
    
    ofVec2f markPoint;
    
    ofRectangle squareStateUi;
    ofRectangle ellipseStateUi;
};

class Turing {
public:
    Turing();
    ~Turing(){};
    void init(int w, int x_res, int y_res);
    
    void update(int speed);
    
    void press(int x, int y){
        for(int i = 0; i < 4; i++){
            states[i].press(x, y);
        };
        if(zone.inside(x,y)){
            int xx = ofMap(x, zone.x, zone.x + zone.width, 0, turing_x_resolution);
            int yy = ofMap(y, zone.y, zone.y + zone.height, 0, turing_y_resolution);
            int index = yy * turing_x_resolution + xx;
            turing_tape[index] = !turing_tape[index];
        }
    };
    
    void setStatePos(ofRectangle rec, int index, int in_pos);
    void drawUi();
    void drawCanvas(int x, int y);
    ofVec2f readPos;
    
    ofRectangle zone;

private:
    TuringState states[4];
    ofColor clr[4];
    
    TuringState currentState;
    ofColor currentClr;
    
    int currentStateIndex = 0;
    int lastStateIndex = 0;
    
    int read_index = 0;
    bool current_read = false;
    
    int read_pos = 0;
    vector<bool> turing_tape;
    unsigned long move_head = 0;
    
    //Canvass
    int turing_x_resolution = 250;
    int turing_y_resolution = 250;
    int turing_width = 500;
};



#endif /* Turing_hpp */
