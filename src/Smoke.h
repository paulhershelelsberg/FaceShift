//
//  Smoke.h
//  FaceFollowFinal
//
//  Created by Paul Hershel Elsberg on 5/26/15.
//
//

#ifndef __FaceFollowFinal__Smoke__
#define __FaceFollowFinal__Smoke__

#include <stdio.h>
#include <ofMain.h>
class Smoke{
public :

    
Smoke();
void setup(float x, float y, float z);
void update();
void draw();

ofVec3f pos;
ofVec3f birth;
ofVec3f vel;
float rad;
ofColor myColor;
float rot;


};


#endif /* defined(__FaceFollowFinal__Smoke__) */
