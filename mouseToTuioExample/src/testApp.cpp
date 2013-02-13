#include "testApp.h"

ofxTuioServer myTuioServer;
TuioCursor * cursor;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(200, 200, 200);
	ofSetVerticalSync(false);

	//Connect to Port
	myTuioServer.start("127.0.0.1",3333);
	myTuioServer.setVerbose(true);
}

//--------------------------------------------------------------
void testApp::update(){
	//send the OSC messages
	myTuioServer.run();
}

//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	cursor = myTuioServer.addCursor(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	myTuioServer.updateCursor(cursor,x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	myTuioServer.removeCursor(cursor);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
