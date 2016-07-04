#pragma once
#include "BaseScene.h"

class DrawingScene : public BaseScene
{

public:

	ofShader* shader;

	float polylineResolution;

	vector<ofPolyline> leftControllerPolylines;
	vector<ofPolyline> rightControllerPolylines;
	bool bIsLeftTriggerPressed;
	bool bIsRightTriggerPressed;
	ofVec3f leftControllerPosition;
	ofVec3f rightControllerPosition;
	ofVec3f lastLeftControllerPosition;
	ofVec3f lastRightControllerPosition;

	void setup(ofxOpenVR* openVR_, ofShader* shader_)
	{
		openVR = openVR_;
		shader = shader_;
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
		if (shader) {
			ofMatrix4x4 currentViewProjectionMatrix = openVR->getCurrentViewProjectionMatrix(nEye);

			shader->begin();
			shader->setUniformMatrix4f("matrix", currentViewProjectionMatrix, 1);
			ofSetColor(ofColor::white);
			for (auto pl : leftControllerPolylines) {
				pl.draw();
			}

			for (auto pl : rightControllerPolylines) {
				pl.draw();
			}
			shader->end();
		}
		// Loading matrices
		else {
			ofPushView();
			ofSetMatrixMode(OF_MATRIX_PROJECTION);
			ofLoadMatrix(openVR->getCurrentProjectionMatrix(nEye));
			ofSetMatrixMode(OF_MATRIX_MODELVIEW);
			ofMatrix4x4 currentViewMatrixInvertY = openVR->getCurrentViewMatrix(nEye);
			currentViewMatrixInvertY.scale(1.0f, -1.0f, 1.0f);
			ofLoadMatrix(currentViewMatrixInvertY);

			ofSetColor(ofColor::white);

			for (auto pl : leftControllerPolylines) {
				pl.draw();
			}

			for (auto pl : rightControllerPolylines) {
				pl.draw();
			}
			ofPopView();
		}
	};

	void onControllerEvent(ofxOpenVRControllerEventArgs args)
	{
		//cout << "ofApp::controllerEvent > role: " << ofToString(args.controllerRole) << " - event type: " << ofToString(args.eventType) << " - button type: " << ofToString(args.buttonType) << " - x: " << args.analogInput_xAxis << " - y: " << args.analogInput_yAxis << endl;
		// Left
		if (args.controllerRole == ControllerRole::Left) {
			// Trigger
			if (args.buttonType == ButtonType::ButtonTrigger) {
				if (args.eventType == EventType::ButtonPress) {
					bIsLeftTriggerPressed = true;

					if (leftControllerPolylines.size() == 0) {
						leftControllerPolylines.push_back(ofPolyline());
						lastLeftControllerPosition.set(ofVec3f());
					}
				}
				else if (args.eventType == EventType::ButtonUnpress) {
					bIsLeftTriggerPressed = false;
				}
			}
			// ButtonTouchpad
			else if (args.buttonType == ButtonType::ButtonTouchpad) {
				if (args.eventType == EventType::ButtonPress) {
					leftControllerPolylines.push_back(ofPolyline());
					lastLeftControllerPosition.set(ofVec3f());
				}
			}
			// Grip
			else if (args.buttonType == ButtonType::ButtonGrip) {
				if (args.eventType == EventType::ButtonPress) {
					for (auto pl : leftControllerPolylines) {
						pl.clear();
					}

					leftControllerPolylines.clear();
				}
			}
		}

		// Right
		else if (args.controllerRole == ControllerRole::Right) {
			// Trigger
			if (args.buttonType == ButtonType::ButtonTrigger) {
				if (args.eventType == EventType::ButtonPress) {
					bIsRightTriggerPressed = true;

					if (rightControllerPolylines.size() == 0) {
						rightControllerPolylines.push_back(ofPolyline());
						lastRightControllerPosition.set(ofVec3f());
					}
				}
				else if (args.eventType == EventType::ButtonUnpress) {
					bIsRightTriggerPressed = false;
				}
			}
			// ButtonTouchpad
			else if (args.buttonType == ButtonType::ButtonTouchpad) {
				if (args.eventType == EventType::ButtonPress) {
					rightControllerPolylines.push_back(ofPolyline());
					lastRightControllerPosition.set(ofVec3f());
				}
			}
			// Grip
			else if (args.buttonType == ButtonType::ButtonGrip) {
				if (args.eventType == EventType::ButtonPress) {
					for (auto pl : rightControllerPolylines) {
						pl.clear();
					}

					rightControllerPolylines.clear();
				}
			}
		}
	};

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