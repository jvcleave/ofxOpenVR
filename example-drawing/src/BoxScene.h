#pragma once
#include "BaseScene.h"

class BoxScene : public BaseScene
{

public:

	ofShader shader;

	bool bIsLeftTriggerPressed;
	bool bIsRightTriggerPressed;
	ofVec3f leftControllerPosition;
	ofVec3f rightControllerPosition;
	ofVec3f lastLeftControllerPosition;
	ofVec3f lastRightControllerPosition;
	ofMatrix4x4 translateMatrix;


	bool isTextureReady;
	void setup(ofxOpenVR* openVR_)
	{
		openVR = openVR_;
		shader.load("default");
		bIsLeftTriggerPressed = false;
		bIsRightTriggerPressed = false;

		lastLeftControllerPosition.set(ofVec3f());
		lastRightControllerPosition.set(ofVec3f());


	}

	void update()
	{
		if (bIsLeftTriggerPressed) {
			if (openVR->isControllerConnected(vr::TrackedControllerRole_LeftHand))
			{
				leftControllerPosition = openVR->getControllerPose(vr::TrackedControllerRole_LeftHand).getTranslation();
			}
		}

		if (bIsRightTriggerPressed)
		{
			if (openVR->isControllerConnected(vr::TrackedControllerRole_RightHand))
			{
				rightControllerPosition = openVR->getControllerPose(vr::TrackedControllerRole_RightHand).getTranslation();
			}
		}
	}
	void onRender(vr::Hmd_Eye& nEye)
	{
		ofMatrix4x4 currentViewProjectionMatrix = openVR->getCurrentViewProjectionMatrix(nEye);

		ofMatrix4x4 hdmPoseMat = translateMatrix * currentViewProjectionMatrix;

		shader.begin();
		shader.setUniformMatrix4f("matrix", hdmPoseMat, 1);


		shader.end();
	};

	void onLeftButtonPress()
	{
		bIsLeftTriggerPressed = true;
	}

	void onLeftButtonRelease()
	{
		bIsLeftTriggerPressed = false;
	}

	void onLeftTouchPadPress()
	{

	}

	void onLeftTouchPadRelease()
	{

	}

	void onLeftGripPress()
	{

	}

	void onLeftGripRelease()
	{

	}

	void onRightButtonPress()
	{
		bIsRightTriggerPressed = true;
	}

	void onRightButtonRelease()
	{
		bIsRightTriggerPressed = false;
	}
	void onRightTouchPadPress()
	{
	}
	void onRightTouchPadRelease()
	{

	}

	void onRightGripPress()
	{

	}

	void onRightGripRelease()
	{
	}
	

	string getHelpInfo()
	{
		stringstream ss;
		ss << "HELP (press h to toggle): " << endl;
		ss << "Press the Trigger of a controller to draw a line with that specific controller." << endl;
		ss << "Press the Touchpad to star a new line." << endl;
		ss << "Press the Grip button to clear all the lines drawn with that specific controller." << endl;
		ss << "Drawing default 3D models " << openVR->getRenderModelForTrackedDevices() << " (press: m)." << endl;

		return ss.str();
	}
	void onKeyPressed(int key)
	{
		switch (key)
		{
		case '+':
		case '=':
			break;

		case '-':
		case '_':

			break;

		default:
			break;
		}

	}
};