#include "ofApp.h"

using namespace ofxCv;
using namespace cv;
int index1 = 0;
int index2 = 0;
void ofApp::setup() {
    ofSetWindowShape(640,480);
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    finder.setup("haarcascade_frontalface_alt2.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.3);
    cam.initGrabber(640, 480);
    skull.loadImage("skull.png");
    bolt.load("fire017.gif");
    cloud.load("giphy.gif");
    ofEnableAlphaBlending();
    bdisplay=false;
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        finder.update(cam);
    }
    //loop through frames of gif
    if(ofGetElapsedTimeMillis()%3)
    {
        index1++;
        if(index1>cloud.pages.size()-1) index1 = 0;
    }
    if(ofGetElapsedTimeMillis()%3)
    {
        index2++;
        if(index2>bolt.pages.size()-1) index2 = 0;
    }
    
}

void ofApp::draw() {
    cam.draw(0, 0);
    for(int i = 0; i < finder.size(); i++) {
        ofRectangle object = finder.getObjectSmoothed(i);
        skull.setAnchorPercent(.5, .5);
        float scaleAmount = 2. * object.width / skull.getWidth();
        float scaleAmount2 = 1.75 * object.width / skull.getWidth();
        
        ofPushMatrix();
        ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
        ofScale(scaleAmount, scaleAmount);
        if(bdisplay)skull.draw(0, 0);
        
        ofScale(scaleAmount, scaleAmount);
        cloud.pages[index1].draw(-250,-420);
        ofScale(scaleAmount2, scaleAmount2);
        if(bdisplay)bolt.pages[index2].draw(-90, -250);
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(object.getPosition());
        ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
        ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
        ofPopMatrix();
    }
}
void ofApp::mousePressed(int x, int y, int button){
    bdisplay = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bdisplay = false;
}

