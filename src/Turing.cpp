//
//  Turing.cpp
//  AI-turing_gol
//
//  Created by Max Björverud on 2024-02-19.
//

#include "Turing.hpp"

Turing::Turing(){
    states[0].setTrue(0, -1, 0);
    states[0].setFalse(1, 1, 1);
    clr[0] = ofColor::red;
    
    states[1].setFalse(0, 1, 0);
    states[1].setTrue(0, 1, 0);
    clr[1] = ofColor::green;
    
    states[2].setFalse(0, -1, 0);
    states[2].setTrue(2, 0, 0);
    clr[2] = ofColor::blue;
    
    states[3].setFalse(1, 1, 0);
    states[3].setTrue(0, -1, 0);
    clr[3] = ofColor::purple;
    
    
    currentStateIndex = (int)ofRandom(4);
    currentStateIndex = 0;
    currentState = states[currentStateIndex];
    read_index = 0;
};

void Turing::init(int w, int x_res, int y_res){
    turing_x_resolution = x_res;
    turing_y_resolution = y_res;
    turing_tape.clear();
    for(int i = 0; i < turing_x_resolution*turing_y_resolution; i++){
        turing_tape.push_back(ofRandom(100) < 20);
    }
    turing_width = w;
}

void Turing::update(int speed){
    if(ofGetSystemTimeMillis() - move_head > speed){
        if(read_index == 0){
            current_read = turing_tape[read_pos];
            states[lastStateIndex].mark(-1);
            if(turing_tape[read_pos]){
                states[currentStateIndex].mark(0);
            }else{
                states[currentStateIndex].mark(4);
            }
            read_index++;
        }else if(read_index == 1){
            vector<int> res = states[currentStateIndex].update(current_read);
            if(current_read){
                states[currentStateIndex].mark(1);
            }else{
                states[currentStateIndex].mark(5);
            }
            turing_tape[read_pos] = res[2];
            read_index++;
        }else if(read_index == 2){
            vector<int> res = states[currentStateIndex].update(current_read);
            if(current_read){
                states[currentStateIndex].mark(2);
            }else{
                states[currentStateIndex].mark(6);
            }
            lastStateIndex = currentStateIndex;
            currentStateIndex = res[0];
            read_index++;
        }else if(read_index == 3){
            vector<int> res = states[currentStateIndex].update(current_read);
            if(current_read){
                states[lastStateIndex].mark(3);
            }else{
                states[lastStateIndex].mark(7);
            }
            
            read_pos += res[1];
            if(read_pos < 0){
                read_pos = turing_tape.size()-1;
            }else if(read_pos >= turing_tape.size()){
                read_pos = 0;
            }
            read_index = 0;
        }
        
        move_head = ofGetSystemTimeMillis();
    }
}

void Turing::drawCanvas(int x, int y){
    ofPushMatrix();
    ofTranslate(x, y);
    float box_size = float(turing_width) / float(turing_x_resolution);
    for(int i = 0; i < turing_tape.size(); i++){
        int y = i / float(turing_x_resolution);
        int x = i % turing_x_resolution;
        ofFill();
        ofSetColor(255);
        if(turing_tape[i]){
            ofDrawRectangle(x*box_size + box_size*.25, y*box_size + box_size*.25, box_size*.5, box_size*.5);
        } else {
            ofDrawEllipse(x*box_size + box_size*.5, y*box_size + box_size*.5, box_size*.5, box_size*.5);
        }
        
        if(i == read_pos){
            ofNoFill();
            ofSetColor(clr[currentStateIndex]);
            readPos.set(x*box_size + box_size*.5, y*box_size + box_size*.5);
            ofDrawEllipse(x*box_size + box_size*.5, y*box_size + box_size*.5, box_size*.5, box_size*.5);
        }
        
        
    }
    
    ofPopMatrix();
    
    //Draw lines
    ofSetColor(clr[currentStateIndex]);
    ofPolyline pline = states[currentStateIndex].getStartLine();
    pline.addVertex(pline.getVertices().back().x, readPos.y + y);
    pline.addVertex(readPos.x + x, readPos.y + y);
    pline.draw();
}

void Turing::setStatePos(ofRectangle rec, int index, int in_pos){
    states[index].setUi(rec, in_pos);
};

void Turing::drawUi(){
    
    
    
    for(int i  =0; i < 4; i++){
        states[i].drawUi(clr[i]);
    }
}
