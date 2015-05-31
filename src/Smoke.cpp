//
//  Smoke.cpp
//  FaceFollowFinal
//
//  Created by Paul Hershel Elsberg on 5/26/15.
//
//

#include "Smoke.h"

Smoke :: Smoke()
{
    pos = ofVec3f(300,300,10);
    vel = ofVec3f(ofRandom(-2,2),ofRandom(-2,2),ofRandom(-2,2));
    rad = 25;
    rot = 0;
    
}
void Smoke :: setup(float x, float y, float z)
{
    pos = ofVec3f(x,y,z);
    birth = pos;
    myColor = ofColor(238,58,140,20);
  
}
void Smoke::update()
{
    pos+=vel;
    rot+=5;
    float distance = ofDist(birth.x,birth.y,pos.x,pos.y);
//    float bright = ofMap(distance, 0, 100, 0, 255);
//    myColor.setBrightness(bright);
}
void Smoke::draw()
{
    ofSetColor(myColor);
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(rot);
    ofCircle(0,0, rad);
    ofPopMatrix();
}