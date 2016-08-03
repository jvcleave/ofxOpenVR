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

	float movementSpeed = .1;
	float cloudSize = ofGetWidth() / 2;
	float maxBoxSize = 100;
	float spacing = 1;

	bool isTextureReady;
	vector<ofBoxPrimitive> boxes;
	int numBoxesToDraw;
	void setup(ofxOpenVR* openVR_)
	{
		openVR = openVR_;

		// Vertex shader source
		string vertex;

		vertex = "#version 150\n";
		vertex += STRINGIFY(
			uniform mat4 matrix;

		in vec4 position;

		void main() {
			gl_Position = matrix * position;
		}
		);

		// Fragment shader source
		string fragment = "#version 150\n";
		fragment += STRINGIFY(
			out vec4 outputColor;
		void main() {
			outputColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
		);

		// Shader
		shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
		shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
		shader.bindDefaults();
		shader.linkProgram();

		bIsLeftTriggerPressed = false;
		bIsRightTriggerPressed = false;

		lastLeftControllerPosition.set(ofVec3f());
		lastRightControllerPosition.set(ofVec3f());

		for (size_t i = 0; i < 10; i++)
		{
			ofBoxPrimitive box;
			box.set(i);
			box.enableColors();
			boxes.push_back(box);
		}
	}

	void update()
	{
		if (ofGetFrameNum() % 100 == 0)
		{
			if (numBoxesToDraw + 1 < boxes.size())
			{
				numBoxesToDraw++;
			}
			else
			{
				numBoxesToDraw = 1;
			}
		}
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

		


		

		translateMatrix.translate(ofVec3f(0.0, .0, 0.0));
		ofMatrix4x4 hdmPoseMat = translateMatrix * currentViewProjectionMatrix;
		shader.begin();
		shader.setUniformMatrix4f("matrix", hdmPoseMat, 1);
		
		for (int i = 0; i < numBoxesToDraw; i++)
		{
			
			
			int degrees = ofGetFrameNum() % 360;

			ofVec3f point(ofRandom(0, 10), 0, 0);
			ofVec3f point2(ofRandom(0, 100), ofRandom(0, 100), 0);
			boxes[i].setGlobalPosition(point2);
			boxes[i].drawWireframe();

		}
		shader.end();
		
#if 0
		ofPushView();
		ofSetMatrixMode(OF_MATRIX_PROJECTION);
		ofLoadMatrix(currentViewProjectionMatrix);
		ofSetMatrixMode(OF_MATRIX_MODELVIEW);
		ofMatrix4x4 currentViewMatrixInvertY = openVR->getCurrentViewMatrix(nEye);
		currentViewMatrixInvertY.scale(1.0f, -1.0f, 1.0f);
		ofLoadMatrix(currentViewMatrixInvertY);
		
		for (int i = 0; i < boxCount; i++) {
			ofPushMatrix();

			float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
			ofVec3f pos(
				ofSignedNoise(t, 0, 0),
				ofSignedNoise(0, t, 0),
				ofSignedNoise(0, 0, t));

			float boxSize = maxBoxSize * ofNoise(pos.x, pos.y, pos.z);

			pos *= cloudSize;
			ofTranslate(pos);
			ofRotateX(pos.x);
			ofRotateY(pos.y);
			ofRotateZ(pos.z);

			//ofLogo.bind();
			ofFill();
			ofSetColor(255);
			ofDrawBox(boxSize);
			//ofLogo.unbind();

			ofNoFill();
			ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
			ofDrawBox(boxSize * 1.1f);

			ofPopMatrix();
		}
		
		ofPopView();
#endif
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
		ss << "Box Scene: " << endl;


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