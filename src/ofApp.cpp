#include "ofApp.h"
#include<iostream>
using namespace std;
using namespace ofxCv;
using namespace cv;
int index1 = 0;
int index2 = 0;
void ofApp::setup() {
    //set up variables with base values
    w = 640;
    h = 480;
    mouseX=0;
    mouseY=0;
    wVal=10;
    hVal=10;
    hVal1=-350;
    hVal2=-650;
    fX=0;
    fY=0;
    count = 0;

    //enable lighting and setup proper window and graphics settings
    ofSetWindowShape(w,h);
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    ofSetSmoothLighting(true);
//    ofEnableDepthTest();
    
    //create spotlight for paparazzi scene
    flash.setSpotlight();
    
    flash.setSpecularColor(ofColor(255.f,255.f,255.f));
    flash.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
    flash.setSpotlightCutOff( 180 );
    
    // rate of falloff, illumitation decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
    flash.setSpotConcentration( 45 );
    
    //setup Kyle's CV for a frontal face scan
    finder.setup("haarcascade_frontalface_alt2.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.3);
    //initialize all media content
    cam.initGrabber(w, h);
    cap.loadImage("cap.png");
    mon.loadImage("money.png");
    icons.loadImage("icons.png");
    sunglasses.loadImage("sunglasses.png");
    dollarSign.loadImage("dolla.png");
    flag.loadImage("flag.png");
    mic.loadImage("mic.png");
    mic2.loadImage("mic 2.png");
    cam2.loadImage("cam.png");
    camera.loadImage("camera.png");
    barbie.loadImage("barbie.png");
    ken.loadImage("ken.png");
    monBack.loadImage("yacht.jpg");
    makeBack.loadImage("vogue.jpg");
    presBack.loadImage("pres.jpg");
    barbBack.loadImage("barb.jpg");
    papBack.loadImage("papa.jpg");
    col.set(255, 0, 0);
    ofEnableAlphaBlending();
   
    //intitialize all booleans
    bdisplay=true;
    iconDisplay = true;
    money=false;
    makeUp=false;
    influence=false;
    papa=false;
    lovers=false;
    //set circles for makeUP CV scene
    ofSetCircleResolution(20);
    //Set background threshold image that we are going to create the mask from
    background.setLearningTime(900);
    background.setThresholdValue(40);
    //setup our shader
    shader.load( "shaderVert.c", "shaderFrag.c" );
    //create fbo
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
}

void ofApp::update() {
    //update web cam feed
    cam.update();
    //set angle and position of light in 3d space
    flash.setOrientation( ofVec3f( 0, 0, 0) );
//    flash.setPosition( ofGetWidth()/2, ofGetHeight()/2, -20);
    flash.setPosition( fX, fY, 200);
    //quickly switch the light position to create flashes in the paparazzi scene
    if(papa)
    {
        if(ofGetElapsedTimeMillis()%3)
        {
            fX=638;
            fY=480;
        }
        if(ofGetElapsedTimeMillis()%4)
        {
            fX=632;
            fY=25;
        }
        if(ofGetElapsedTimeMillis()%5)
        {
            fX=3;
            fY=476;
        }
        if(ofGetElapsedTimeMillis()%7)
        {
            fX=0;
            fY=0;
        }
    }
    
    if(cam.isFrameNew()) {
        finder.update(cam);//update cv
        background.update(cam, thresholded);//create the alpha mask
        thresholded.update();//update the mask
        original.setFromPixels(cam.getPixelsRef());//create pixel reference of the webcam
        destination=original;//set our destination to the cam reference
        destination.applyMask(thresholded);//apply the mask to the original

    }
    //create three raining money image location values
    if(money)
    {
        if(hVal==470)
        {
            hVal=-350;
        }
        hVal++;
        if(hVal1==470)
        {
            hVal1=-350;
        }
        hVal1++;
        if(hVal2==470)
        {
            hVal2=-350;
        }
        hVal2++;
    }
    //if the perlin noise becomes too much take us back to the original
    if(count>3000)
    {
        bdisplay=true;
        makeUp=false;
        lovers=false;
        money=false;
        influence=false;
        papa=false;
        
    }
  
}

void ofApp::draw() {
    fbo.begin();
        //base lighting off of paparazzi scene
        if(papa)ofEnableLighting();
        if(papa)flash.enable();
        if (!papa) flash.disable();
    ofSetColor(255,255,255);
    //draw different background images based on booleans
    if(bdisplay)cam.draw(0, 0);//place backgrounds here
    if(makeUp)makeBack.draw(0, 0, ofGetWidth(), ofGetHeight());
    if(money)monBack.draw(0, 0, ofGetWidth(), ofGetHeight());
    if(papa)papBack.draw(0, 0, ofGetWidth(), ofGetHeight());
    if(lovers)barbBack.draw(0, 0, ofGetWidth(), ofGetHeight());
    if(influence)presBack.draw(0, 0, ofGetWidth(), ofGetHeight());
    //draw webcam on top of background
    destination.draw(0,0);
    //create the raining money
    if(money)
    {
        mon.draw(0, hVal,ofGetWidth(),ofGetHeight());
        mon.draw(0, hVal1, ofGetWidth(), ofGetHeight());
        mon.draw(0, hVal2, ofGetWidth(), ofGetHeight());

    }
    //decided against drawing cameras and microphones in the scene because it looks weird with the lighting
//    if(papa)
//    {
//        for(int i = 0;i<30;i++)
//        {
////            cam2.draw(i*20,(sin(i)*200)+200);
////            camera.draw(i*20,(cos(i)*200)+200);
////            mic.draw((i*5)+150,(sin(i)*50)+380);
////            mic2.draw((i*5)+300,(sin(i)*50)+380);
////            ofSetColor(255, 0, 0);
////            ofEllipse(i*20+25, (sin(i)*200)+225, 5, 5);
////            ofEllipse(i*20+25, (cos(i)*200)+225, 5, 5);
////
////            ofSetColor(255, 255, 255);
//
//        }
//    }
    //draw ken and barbie images for the lovers scene
    if(lovers)
    {
        ken.draw(300, 200);
        barbie.draw(0, 100);
    }
    //draw the right side icon panel as the top layer
       icons.draw(440, 40);


    //perform ofxCV calculations
    for(int i = 0; i < finder.size(); i++) {
        ofRectangle object = finder.getObjectSmoothed(i);
        cap.setAnchorPercent(.5, .5);
        //create different scales for positioning of cv objects
        float scaleAmount = 1. * object.width / cap.getWidth();
        float scaleAmount2 = .75 * object.width / sunglasses.getWidth();
        //create the pres flag and cap at appropriate position
        ofPushMatrix();
        ofTranslate(object.x + object.width / 2., object.y + object.height * -.12);
        ofScale(scaleAmount, scaleAmount);
        if(influence)
        {
            cap.draw(0, 0);
            flag.draw(50,20);
        }
        ofScale(scaleAmount, scaleAmount);
        ofPopMatrix();
        //create the sunglasses and dollar signs on the shades at appropriate positions
        ofPushMatrix();
        ofTranslate(object.x + object.width / 4.5, object.y + object.height * .32);
        ofScale(scaleAmount2, scaleAmount2);
        if(money)
        {
          sunglasses.draw(-75, 0);
          dollarSign.draw(0, 20);
          dollarSign.draw(270, 20);

        }
        //create a vector of small semi transparent smoke bubbles that are generated from the face in all directions
        if(makeUp)
        {
            Smoke newSmoke;
            //positioning of bubbles
            newSmoke.setup((object.x + object.width / 2.)-ofRandom(300), (object.y + object.height * -.12)-ofRandom(-200,200), 10);
            smoke.push_back(newSmoke);//add to stack
            for(int i =0; i<smoke.size();i++)
            {
                smoke[i].update();
            }
            
            for (int i = 0; i<smoke.size();i++)
            {
                //erase the smoke if it gets too far away from its original position
                float distance = ofDist(smoke[i].birth.x, smoke[i].birth.y, smoke[i].pos.x, smoke[i].pos.y);
                smoke[i].draw();
                if (distance>100){
                    smoke.erase(smoke.begin()+i);
                    i--;
                }
            }
            
        }

        ofScale(scaleAmount2, scaleAmount2);
        ofPopMatrix();
        //commented out the string and line that shows cv tracking for reference
//        ofPushMatrix();
//        ofTranslate(object.getPosition());
//        ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
//        ofLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
//        ofPopMatrix();
    }
    
        if(papa)ofDisableLighting();
    fbo.end();
    //if not the original feed then begin incrementing the uniform float we pass to the shader file
    if(!bdisplay)
    {
    shader.begin();
    int time = ofGetElapsedTimef();
        if(time % 15)
        {
            count++;
        }
        
//    cout<<count<<endl; //testing
    shader.setUniform1f( "time", count/50 );	//Passing float parameter "time" to shader

    }
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);//draw the fbo with all our images and content confined within the bounds of the shader
    if(!bdisplay)shader.end();

    
}
void ofApp::mousePressed(int x, int y, int button){
    //all of these mouse pressed spaces are links to the side icons on the icon panel starting from the top down and we reset the count to allow for the shader to slowly increase when a new setting is selected
    if((x>506)&&(x<576)&&(y>45)&&(y<115))
    {
        makeUp=true;
        money=false;
        influence=false;
        papa=false;
        lovers=false;
        bdisplay=false;
        count=0-ofGetElapsedTimef();


    }
    if((x>469)&&(x<609)&&(y>126)&&(y<186))
    {
        money=true;
        makeUp=false;
        influence=false;
        papa=false;
        lovers=false;
        bdisplay=false;
        count=0-ofGetElapsedTimef();


    }
    if((x>500)&&(x<580)&&(y>190)&&(y<270))
    {
        papa=true;
        money=false;
        makeUp=false;
        influence=false;
        lovers=false;
        bdisplay=false;
        count=0-ofGetElapsedTimef();



    }
    if((x>492)&&(x<587)&&(y>284)&&(y<376))
    {
        influence=true;
        money=false;
        makeUp=false;
        papa=false;
        lovers=false;
        bdisplay=false;
        count=0-ofGetElapsedTimef();


        
    }
    if((x>478)&&(x<603)&&(y>383)&&(y<468))
    {
        lovers=true;
        money=false;
        makeUp=false;
        influence=false;
        papa=false;
        bdisplay=false;
        count=0-ofGetElapsedTimef();

    }

    if((!papa)&&(!influence)&&(!lovers)&&(!money)&&(!makeUp))
    {
        bdisplay=true;
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bdisplay = false;
}
//get mouse info
void ofApp::mouseMoved(int x, int y){
    mouseX=x;
    mouseY=y;
   
//    cout<<"x" <<endl;
//    cout<<mouseX<<endl;
//    cout<<"y"<<endl;
//    cout<<mouseY<<endl;

}
void ofApp::keyPressed(int key)
{
    //used for testing purposes
    if(key=='d')wVal+=10;
    if(key=='a')wVal-=10;
    if(key=='w')hVal+=10;
    if(key=='x')hVal-=10;
    //press the space bar to reset the mask of the webcam feed
    if(key == ' ') {
        background.reset();
    }
    
}