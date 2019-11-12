#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	ofSetLogLevel(OF_LOG_NOTICE);
	//Connect to Port
	myTuio.connect(3333);

	//Assign Global TUIO Callback Functions
	ofAddListener(myTuio.touchDown, this, &ofApp::touchDown);
	ofAddListener(myTuio.touchUp, this, &ofApp::touchUp);
	ofAddListener(myTuio.touchMoved, this, &ofApp::touchMoved);
}

//--------------------------------------------------------------
void ofApp::update(){
	myTuio.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	myTuio.drawCursors();
	myTuio.drawObjects();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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

void ofApp::exit()
{
	ofRemoveListener(myTuio.touchDown, this, &ofApp::touchDown);
	ofRemoveListener(myTuio.touchUp, this, &ofApp::touchUp);
	ofRemoveListener(myTuio.touchMoved, this, &ofApp::touchMoved);
}
void ofApp::touchDown(ofTouchEventArgs & touch) {
	ofLogNotice("ofApp::touchDown") << " cursor added: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y);
}

void ofApp::touchUp(ofTouchEventArgs & touch) {
	ofLogNotice("ofApp::touchUp") << " cursor removed: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y);
}

void ofApp::touchMoved(ofTouchEventArgs & touch) {
	ofLogNotice("ofApp::touchMoved") << " cursor updated: " + ofToString(touch.id) +
		" X: " + ofToString(touch.x) +
		" Y: " + ofToString(touch.y);
}