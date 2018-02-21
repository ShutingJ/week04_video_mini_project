#pragma once

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxOpenCv.h"

class Color {
public:
    float hue, sat, bri;
    ofxVec2f pos;
};

//#define _USE_LIVE_VIDEO
// uncomment this to use a live camera
// otherwise, we'll use a movie file

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int wWidth;
    int wHeight;
    
    int hue, sat, val;
    bool drawEnabled;
    
    ofVideoGrabber        wCam;
    ofxCvColorImage        origOutput;
    ofxCvColorImage        origOutputHSV;
    
    ofxCvGrayscaleImage hueOutput;
    ofxCvGrayscaleImage satOutput;
    ofxCvGrayscaleImage briOutput;
    
    unsigned char *        lockedOnPixels;
    ofTexture            lockedOnTexture;
    
    ofxCvGrayscaleImage    lockedOutput;
    ofxCvContourFinder    lockedContours;
    
    unsigned char *        scribblePixels;
    ofTexture            scribbleOutput;
	

};


