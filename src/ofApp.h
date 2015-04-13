// Face Tracking Grateful Dead Lightning Strike by Paul Elsberg
//April 12, 2015

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGif.h"
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    ofImage skull;
    ofxGIF::fiGifLoader cloud;
    ofxGIF::fiGifLoader bolt;
    bool bdisplay;
    
};
