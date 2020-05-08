#include "ofMain.h"
#include "ofxTweeny.hpp"

class Camera : public ofEasyCam {
public:
    Camera() : ofEasyCam(){
        pos_ = glm::vec3{0,0,300};
    }
    
    void update(){
        ofEasyCam::setPosition(pos_);
        ofEasyCam::setTarget(glm::vec3(0));
    }
    
    void position(const glm::vec3& to){
        ofxTweeny::Tweener::add(&pos_, pos_, to, 2000, ofxTweeny::easeOutExpo);
    }
    
private:
    glm::vec3 pos_;
};

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
private:
    float radius;
    glm::vec3 pos;
    Camera camera;
};



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    pos = glm::vec3(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxTweeny::Tweener::update();
    camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    ofNoFill();
    ofDrawBox(0, 0, 0, 100);
    camera.end();
}

void ofApp::keyPressed(int key){
    if(key == ' '){
        camera.position(glm::vec3(ofRandom(-100, 100), ofRandom(-100, 100), ofRandom(-100, 100)));
    }
}


int main( ){
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(new ofApp());
}
