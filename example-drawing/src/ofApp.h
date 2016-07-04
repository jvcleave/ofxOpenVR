#pragma once

#include "ofMain.h"
#include "SceneManager.h"
class ofApp : public ofBaseApp {

public:
	void setup();


	void update();
	void draw();
	SceneManager sceneManager;



	void keyPressed(int key);
	
	void exit();

};