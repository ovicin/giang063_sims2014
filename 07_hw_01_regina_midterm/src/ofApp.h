#pragma once

#include "ofMain.h"
#define NUM_PARTICLES 2000


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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofEasyCam       cam;
    ofLight         light;
    
    float dist;
    float noisey;
    
    vector<ofPoint> points;
    
    vector<float> theta;
    vector<float> phi;
    vector<int> radius;
    
    vector<float> changeTheta;
    vector<float> changePhi;
    
    bool isRecording;
    
};

