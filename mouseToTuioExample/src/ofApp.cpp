#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myTuioServer.start("127.0.0.1", 3333);
	myTuioServer.setVerbose(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	myTuioServer.run();
}

//--------------------------------------------------------------
void ofApp::draw(){

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
	myTuioServer.updateCursor(cursor, x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cursor = myTuioServer.addCursor(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	myTuioServer.removeCursor(cursor);
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
