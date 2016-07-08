#pragma once
#include "BaseScene.h"

class DrawingScene : public BaseScene
{

public:

	ofShader shader;

	float polylineResolution;

	vector<ofPolyline> leftControllerPolylines;
	vector<ofPolyline> rightControllerPolylines;
	bool bIsLeftTriggerPressed;
	bool bIsRightTriggerPressed;
	ofVec3f leftControllerPosition;
	ofVec3f rightControllerPosition;
	ofVec3f lastLeftControllerPosition;
	ofVec3f lastRightControllerPosition;

	void setup(ofxOpenVR* openVR_)
	{
		openVR = openVR_;
		shader.load("default");
		bIsLeftTriggerPressed = false;
		bIsRightTriggerPressed = false;

		polylineResolution = .004f;
		lastLeftControllerPosition.set(ofVec3f());
		lastRightControllerPosition.set(ofVec3f());
	}

	void update()
	{
		if (bIsLeftTriggerPressed) {
			if (openVR->isControllerConnected(vr::TrackedControllerRole_LeftHand)) {
				leftControllerPosition = openVR->getControllerPose(vr::TrackedControllerRole_LeftHand).getTranslation();

				if (lastLeftControllerPosition.distance(leftControllerPosition) >= polylineResolution) {
					leftControllerPolylines[leftControllerPolylines.size() - 1].lineTo(leftControllerPosition);
					lastLeftControllerPosition.set(leftControllerPosition);
				}
			}
		}

		if (bIsRightTriggerPressed) {
			if (openVR->isControllerConnected(vr::TrackedControllerRole_RightHand)) {
				rightControllerPosition = openVR->getControllerPose(vr::TrackedControllerRole_RightHand).getTranslation();

				if (lastRightControllerPosition.distance(rightControllerPosition) >= polylineResolution) {
					rightControllerPolylines[rightControllerPolylines.size() - 1].lineTo(rightControllerPosition);
					lastRightControllerPosition = rightControllerPosition;
				}
			}
		}
	}
	void onRender(vr::Hmd_Eye& nEye)
	{
		ofMatrix4x4 currentViewProjectionMatrix = openVR->getCurrentViewProjectionMatrix(nEye);

		shader.begin();
		shader.setUniformMatrix4f("matrix", currentViewProjectionMatrix, 1);
		ofSetColor(ofColor::white);
		for (auto pl : leftControllerPolylines) {
			pl.draw();
		}

		for (auto pl : rightControllerPolylines) {
			pl.draw();
		}
		shader.end();
	};

	void onLeftButtonPress()
	{
		bIsLeftTriggerPressed = true;

		if (leftControllerPolylines.size() == 0)
		{
			leftControllerPolylines.push_back(ofPolyline());
			lastLeftControllerPosition.set(ofVec3f());
		}
	}

	void onLeftButtonRelease()
	{
		bIsLeftTriggerPressed = false;
	}

	void onLeftTouchPadPress()
	{
		leftControllerPolylines.push_back(ofPolyline());
		lastLeftControllerPosition.set(ofVec3f());
	}

	void onLeftTouchPadRelease()
	{
		
	}

	void onLeftGripPress()
	{
		for (auto pl : leftControllerPolylines)
		{
			pl.clear();
		}

		leftControllerPolylines.clear();
	}

	void onLeftGripRelease()
	{

	}

	void onRightButtonPress()
	{
		bIsRightTriggerPressed = true;

		if (rightControllerPolylines.size() == 0) {
			rightControllerPolylines.push_back(ofPolyline());
			lastRightControllerPosition.set(ofVec3f());
		}
	}

	void onRightButtonRelease()
	{
		bIsRightTriggerPressed = false;
	}
	void onRightTouchPadPress()
	{
		rightControllerPolylines.push_back(ofPolyline());
		lastRightControllerPosition.set(ofVec3f());
	}
	void onRightTouchPadRelease()
	{

	}

	void onRightGripPress()
	{
		for (auto pl : rightControllerPolylines) {
			pl.clear();
		}

		rightControllerPolylines.clear();
		cout << "onRightGripPress" << endl;

	}

	void onRightGripRelease()
	{
		cout << "onRightGripRelease" << endl;
	}
	

	string getHelpInfo()
	{
		stringstream ss;
		ss << "HELP (press h to toggle): " << endl;
		ss << "Press the Trigger of a controller to draw a line with that specific controller." << endl;
		ss << "Press the Touchpad to star a new line." << endl;
		ss << "Press the Grip button to clear all the lines drawn with that specific controller." << endl;
		ss << "Drawing resolution " << polylineResolution << " (press: +/-)." << endl;
		ss << "Drawing default 3D models " << openVR->getRenderModelForTrackedDevices() << " (press: m)." << endl;

		return ss.str();
	}
	void onKeyPressed(int key)
	{
		switch (key) {
		case '+':
		case '=':
			polylineResolution += .0001f;
			break;

		case '-':
		case '_':
			polylineResolution -= .0001f;
			if (polylineResolution < 0) {
				polylineResolution = 0;
			}
			break;

		default:
			break;
		}

		cout << polylineResolution << endl;
	}
};