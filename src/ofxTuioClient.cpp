/*
 TUIO Client Wrapper for OpenFrameworks 
 Copyright (c) 2009 Matthias Dörfelt <info@mokafolio.de>
 Based on the TUIO Demo by Martin Kaltenbrunner:
 
 Copyright (c) 2005-2009 Martin Kaltenbrunner <mkalten@iua.upf.edu>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ofxTuioClient.h"

ofxTuioClient::ofxTuioClient() {
    bIsConnected = false;	
	bVerbose = false;
}

void ofxTuioClient::connect(int port){
	client = new TuioClient(port);
	client->addTuioListener(this);
	client->connect();
	
	if (!client->isConnected()) {
		ofLogError("Could not connect TUIO Client");
	} else {
	    bIsConnected = true;	
	}
	
}

void ofxTuioClient::disconnect(){
	if(bIsConnected) client->disconnect();
	bIsConnected = false;
}

void ofxTuioClient::setVerbose(bool b){
	bVerbose = b;
}

void ofxTuioClient::drawCursors(){
	ofPushStyle();
    std::list<TuioCursor*> cursorList = client->getTuioCursors();
	std::list<TuioCursor*>::iterator tit;
	client->lockCursorList();
	for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
		TuioCursor * cur = (*tit);
		//if(tcur!=0){
			//TuioCursor cur = *tcur;
			ofSetColor(0.0,0.0,0.0);
			ofDrawEllipse(cur->getX()*ofGetWidth(), cur->getY()*ofGetHeight(), 10.0, 10.0);
			string str = "SessionId: "+ofToString((int)(cur->getSessionID()));
			ofDrawBitmapString(str, cur->getX()*ofGetWidth()-10.0, cur->getY()*ofGetHeight()+25.0);
			str = "CursorId: "+ofToString((int)(cur->getCursorID()));
			ofDrawBitmapString(str, cur->getX()*ofGetWidth()-10.0, cur->getY()*ofGetHeight()+40.0);
		//}
	}
	client->unlockCursorList();
	ofPopStyle();
}

void ofxTuioClient::drawObjects(){
	ofPushStyle();
    std::list<TuioObject*> objectList = client->getTuioObjects();
	list<TuioObject*>::iterator tobj;
	client->lockObjectList();
	for (tobj=objectList.begin(); tobj != objectList.end(); tobj++) {
		TuioObject *obj = (*tobj);
		glColor3f(1.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(obj->getX()*ofGetWidth(), obj->getY()*ofGetHeight(), 0.0);
		glRotatef(obj->getAngleDegrees(), 0.0, 0.0, 1.0);
		ofDrawRectangle(-10.0, -10.0, 20.0, 20.0);
		glColor3f(1.0,1.0,1.0);
		ofDrawLine(0, 0, 0, -10);
		glPopMatrix();
		string str = "SymbolId: "+ofToString((int)(obj->getSymbolID()));
		ofDrawBitmapString(str, obj->getX()*ofGetWidth()-10.0, obj->getY()*ofGetHeight()+25.0);
		str = "SessionId: "+ofToString((int)(obj->getSessionID()));
		ofDrawBitmapString(str, obj->getX()*ofGetWidth()-10.0, obj->getY()*ofGetHeight()+40.0);
	}
	client->unlockObjectList();
	ofPopStyle();
}

void ofxTuioClient::update(){
	TuioObject tobj;
	while(objectAddedQueue.tryReceive(tobj)){
		ofNotifyEvent(objectAdded, tobj, this);
	}
	while(objectUpdatedQueue.tryReceive(tobj)){
		ofNotifyEvent(objectUpdated, tobj, this);
	}
	while(objectRemovedQueue.tryReceive(tobj)){
		ofNotifyEvent(objectRemoved, tobj, this);
	}

	ofTouchEventArgs touch;
	while(touchAddedQueue.tryReceive(touch)){
		ofNotifyEvent(touchDown, touch, this);
	}
	while(touchUpdatedQueue.tryReceive(touch)){
		ofNotifyEvent(touchMoved, touch, this);
	}
	while(touchRemovedQueue.tryReceive(touch)){
		ofNotifyEvent(touchUp, touch, this);
	}
}


void ofxTuioClient::addTuioObject(TuioObject *tobj) {
	
	if(bFlip){
		tobj->setX(1.f - tobj->getX());
		tobj->setY(1.f - tobj->getY());
	}
	objectAddedQueue.send(*tobj);
	
	if (bVerbose)
		std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
	
}

void ofxTuioClient::updateTuioObject(TuioObject *tobj) {
	
	if(bFlip){
		tobj->setX(1.f - tobj->getX());
		tobj->setY(1.f - tobj->getY());
	}
	objectUpdatedQueue.send(*tobj);
	
	if (bVerbose) 	
		std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() 
		<< " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
	
}

void ofxTuioClient::removeTuioObject(TuioObject *tobj) {
	
	if(bFlip){
		tobj->setX(1.f - tobj->getX());
		tobj->setY(1.f - tobj->getY());
	}
	objectRemovedQueue.send(*tobj);
	
	if (bVerbose)
		std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}

void ofxTuioClient::addTuioCursor(TuioCursor *tcur) {
	ofTouchEventArgs touch;
	touch.x=tcur->getX();
	touch.y=tcur->getY();
	touch.id=tcur->getSessionID();
	
	if(bFlip){
		touch.x = 1.f - touch.x;
		touch.y = 1.f - touch.y;
	}

	touchAddedQueue.send(touch);
	
	if (bVerbose) 
		std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;
	
}

void ofxTuioClient::updateTuioCursor(TuioCursor *tcur) {

	ofTouchEventArgs touch;
	touch.x=tcur->getX();
	touch.y=tcur->getY();
	touch.id=tcur->getSessionID();
	
	if(bFlip){
		touch.x = 1.f - touch.x;
		touch.y = 1.f - touch.y;
	}
	touchUpdatedQueue.send(touch);
	
	if (bVerbose) 	
		std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
		<< " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void ofxTuioClient::removeTuioCursor(TuioCursor *tcur) {

	ofTouchEventArgs touch;
	touch.x=tcur->getX();
	touch.y=tcur->getY();
	touch.id=tcur->getSessionID();
	
	if(bFlip){
		touch.x = 1.f - touch.x;
		touch.y = 1.f - touch.y;
	}
	touchRemovedQueue.send(touch);
	
	if (bVerbose)
		std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

void ofxTuioClient::refresh(TuioTime frameTime) {
	
}
