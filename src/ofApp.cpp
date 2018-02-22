#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    wWidth  = 320;
    wHeight = 240;
    
    hue = 0;
    sat = 0;
    val = 0;
    
    drawEnabled = true;
    
    wCam.initGrabber(wWidth, wHeight);
    
    origOutput.allocate(wWidth, wHeight);
    origOutputHSV.allocate(wWidth, wHeight);
    
    hueOutput.allocate(wWidth, wHeight);
    satOutput.allocate(wWidth, wHeight);
    briOutput.allocate(wWidth, wHeight);
    
    lockedOnPixels = new unsigned char [wWidth * wHeight];
    lockedOnTexture.allocate(wWidth, wHeight, GL_LUMINANCE);
    
    lockedOutput.allocate(wWidth, wHeight);
    
    scribblePixels = new unsigned char[wWidth * wHeight];
    for (int i = 0; i < (wWidth * wHeight); i++) {
        scribblePixels[i] = 0;
    }
    scribbleOutput.allocate(wWidth, wHeight, GL_LUMINANCE);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    wCam.update();
    if (wCam.isFrameNew()) {
        origOutput.setFromPixels(wCam.getPixels());
        
        origOutputHSV = origOutput;
        origOutputHSV.convertRgbToHsv();
        
        origOutputHSV.convertToGrayscalePlanarImages(hueOutput, satOutput, briOutput);
        
        hueOutput.flagImageChanged();
        satOutput.flagImageChanged();
        briOutput.flagImageChanged();
        
        unsigned char * huePixels = hueOutput.getPixels().getData();
        unsigned char * satPixels = satOutput.getPixels().getData();
        unsigned char * briPixels = briOutput.getPixels().getData();
        
        for (int i = 0; i < (wWidth * wHeight); i++) {
            if ((huePixels[i] >= hue-12  && huePixels[i] <= hue+12) &&
                (satPixels[i] >= sat-24 && satPixels[i] <= sat+200)) {
                //lockedOnPixels[i] = CV_RGB(255, 0, 0);
            } else {
                lockedOnPixels[i] = 0;
            }
        }

        lockedOutput.setFromPixels(lockedOnPixels, wWidth, wHeight);
        
        lockedContours.findContours(lockedOutput, 160, (wWidth * wHeight) / 3, 1, false, true);
        
        lockedOnTexture.loadData(lockedOnPixels, wWidth, wHeight, GL_LUMINANCE);
        
        if (lockedContours.blobs.size() > 0 && drawEnabled) {
            int lineWidth = 3;
            
            for (int i = -lineWidth; i <= lineWidth; i++) {
                for (int j = -lineWidth; j <= lineWidth; j++) {
                    scribblePixels[((int)(lockedContours.blobs.at(0).centroid.y + i) * wWidth) + (int)((wWidth - lineWidth - 1) - lockedContours.blobs.at(0).centroid.x + j)] = 128;
                }
            }
        }
        
        scribbleOutput.loadData(scribblePixels, wWidth, wHeight, GL_LUMINANCE);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(100, 100, 100);
    
    ofSetColor(0xffffff);
    
    wCam.draw(0,0);
    origOutputHSV.draw(360, 0);
    lockedContours.draw();
    
    lockedOnTexture.draw(720, 0);
    //ofDrawBitmapString("red", 720, 20);
    scribbleOutput.draw(360, 260);
    
    char tmpStr[255];
    sprintf(tmpStr, "h: %i\ns: %i\nv: %i", hue, sat, val);
    ofDrawBitmapString(tmpStr, 20, 260);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_BACKSPACE) {
        for (int i = 0; i < (wWidth * wHeight); i++) {
            scribblePixels[i] = 0;
        }
    }
    
    if (key == OF_KEY_RETURN) { drawEnabled = false; }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == OF_KEY_RETURN) { drawEnabled = true; }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    unsigned char * huePixels = hueOutput.getPixels().getData();
    unsigned char * satPixels = satOutput.getPixels().getData();
    unsigned char * briPixels = briOutput.getPixels().getData();
    
    hue = huePixels[x + (y * hueOutput.width)];
    sat = satPixels[x + (y * satOutput.width)];
    val = briPixels[x + (y * briOutput.width)];
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
