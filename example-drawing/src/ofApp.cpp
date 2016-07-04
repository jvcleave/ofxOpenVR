#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	sceneManager.setup();

}



//--------------------------------------------------------------
void ofApp::update(){
	
	sceneManager.update();

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	sceneManager.draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	sceneManager.onKeyPressed(key);
	
}


//--------------------------------------------------------------
void ofApp::exit() {

	sceneManager.exit();
}

