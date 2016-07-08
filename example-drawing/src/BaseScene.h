#pragma once
#include "ofxOpenVR.h"
#include "ofMain.h"
#include "ControllerListener.h"

class BaseScene: public ControllerListener
{
public:


	ofxOpenVR* openVR;
	BaseScene()
	{
		openVR = NULL;

	}
	virtual void setup(ofxOpenVR*) = 0;
	virtual void update() = 0;
	virtual void onRender(vr::Hmd_Eye& nEye)=0;
	virtual void onKeyPressed(int key) = 0;
	virtual string getHelpInfo() = 0;
};