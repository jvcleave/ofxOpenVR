#pragma once
#pragma once
#include "BaseScene.h"

class VideoScene : public BaseScene
{
	 
public:

	ofShader shader;

	ofVideoPlayer videoPlayer;
	bool bIsLeftTriggerPressed;
	bool bIsRightTriggerPressed;
	ofVec3f leftControllerPosition;
	ofVec3f rightControllerPosition;
	ofVec3f lastLeftControllerPosition;
	ofVec3f lastRightControllerPosition;
	ofMatrix4x4 translateMatrix;
	ofBoxPrimitive box;
	ofBoxPrimitive plane;

	bool isTextureReady;
	void setup(ofxOpenVR* openVR_)
	{
		openVR = openVR_;
		string vertex;

		vertex = "#version 150\n";
		vertex += STRINGIFY(
			uniform mat4 matrix;

		in vec4  position;
		in vec2  texcoord;

		out vec2 texCoordVarying;

		void main()
		{
			texCoordVarying = texcoord;
			gl_Position = matrix * position;

		}
		);

		// Fragment shader source
		string fragment = "#version 150\n";
		fragment += STRINGIFY(
			uniform sampler2DRect baseTex;

		in vec2 texCoordVarying;

		out vec4 fragColor;

		vec2 texcoord0 = texCoordVarying;

		void main() {
			vec2 tx = texcoord0;
			tx.y = 256.0 - tx.y;
			vec4 image = texture(baseTex, tx);
			fragColor = image;
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

		//ofEnableNormalizedTexCoords();
		//fingers.mov
		//ukythkK4EPQ.mp4
		videoPlayer.load("fingers.mov");
		videoPlayer.play();
		translateMatrix.translate(ofVec3f(0.0, .0, 0.0));
		translateMatrix.rotate(90, 1.0, 0.0, 0.0);
		translateMatrix.scale(10, 10, 10);
		isTextureReady = false;
		box.set(1);
		box.enableColors();
		plane.set(1);
		plane.enableColors();

	}

	void update()
	{
	
		videoPlayer.update();
		if (!isTextureReady)
		{
			if (videoPlayer.getTexture().isAllocated())
			{
				box.mapTexCoordsFromTexture(videoPlayer.getTexture());
				isTextureReady = true;
				ofLogVerbose() << "isTextureReady: " << isTextureReady;
				//plane.resizeToTexture(videoPlayer.getTexture());
				plane.mapTexCoordsFromTexture(videoPlayer.getTexture());
				plane.setDepth(0.02);
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
		if (isTextureReady) {
			ofMatrix4x4 currentViewProjectionMatrix = openVR->getCurrentViewProjectionMatrix(nEye);

			ofMatrix4x4 hdmPoseMat = translateMatrix * currentViewProjectionMatrix;
			/*
			shader->begin();
			shader->setUniformMatrix4f("matrix", hdmPoseMat, 1);
			shader->setUniformTexture("baseTex", videoPlayer.getTextureReference(), 0);
			box.draw();

			shader->end();
			*/
			shader.begin();
			shader.setUniformMatrix4f("matrix", hdmPoseMat, 1);
			shader.setUniformTexture("baseTex", videoPlayer.getTextureReference(), 0);
			plane.draw();
			
			shader.end();
		}
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