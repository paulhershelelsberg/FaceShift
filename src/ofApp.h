// Face Tracking Grateful Dead Lightning Strike by Paul Elsberg
//April 12, 2015

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGif.h"
#include "Smoke.h"
#include "ofxImageMask.h"
class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseMoved (int x, int y);
    void keyPressed(int key);
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    ofImage skull,mon,cap,icons,sunglasses,dollarSign,flag,cam2,mic,mic2,camera,barbie,ken,bath ;
    ofImage monBack, makeBack, presBack,barbBack,kenBack,papBack;
    bool bdisplay,iconDisplay,money,makeUp,influence,papa,lovers,lovers2;
    int w,h,mouseX,mouseY,wVal,hVal,hVal1,hVal2,fX,fY;
    ofColor col;
    ofLight flash;
    vector<Smoke> smoke;
    ofxImageMask destination;
    ofxCv::RunningBackground background;
    ofImage thresholded, original;
    ofShader shader;	//Shader
    ofFbo fbo;
    float count;
};
