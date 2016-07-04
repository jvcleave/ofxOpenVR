#pragma once

#define STRINGIFY(A) #A
#include "DrawingScene.h"

class SceneManager
{
public:

	vector<BaseScene*> scenes;
	BaseScene* currentScene;
	ofxOpenVR openVR;
	ofShader shader;

	bool bShowHelp;
	std::ostringstream _strHelp;

	SceneManager()
	{
		bShowHelp = false;
		_strHelp.str("");
	}

	void setup()
	{
		// We need to pass the method we want ofxOpenVR to call when rending the scene
		openVR.setup(std::bind(&SceneManager::render, this, std::placeholders::_1));
		openVR.setDrawControllers(true);

		ofAddListener(openVR.ofxOpenVRControllerEvent, this, &SceneManager::controllerEvent);

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

		DrawingScene* drawingScene = new DrawingScene();
		drawingScene->setup(&openVR, &shader);
		currentScene = drawingScene;
	}

	void update()
	{
		openVR.update();
		if (currentScene)
		{
			currentScene->update();
		}
		
	}

	void draw()
	{
		openVR.render();
		openVR.renderDistortion();

		openVR.drawDebugInfo(10.0f, 500.0f);

#if 1
		// Help
		if (bShowHelp) {
			_strHelp.str("");
			_strHelp.clear();
			_strHelp << "HELP (press h to toggle): " << endl;
			_strHelp << "Press the Trigger of a controller to draw a line with that specific controller." << endl;
			_strHelp << "Press the Touchpad to star a new line." << endl;
			_strHelp << "Press the Grip button to clear all the lines drawn with that specific controller." << endl;
			//_strHelp << "Drawing resolution " << polylineResolution << " (press: +/-)." << endl;
			ofDrawBitmapStringHighlight(_strHelp.str(), ofPoint(10.0f, 20.0f), ofColor(ofColor::black, 100.0f));
		}
#endif
	}

	void onKeyPressed(int key)
	{
		if (currentScene)
		{
			currentScene->onKeyPressed(key);
		}
	}
	void render(vr::Hmd_Eye nEye)
	{
		if (currentScene)
		{
			currentScene->onRender(nEye);
		}
	}
	void controllerEvent(ofxOpenVRControllerEventArgs& args)
	{
		if (currentScene)
		{
			currentScene->onControllerEvent(args);
		}
	}
	void exit()
	{
		ofRemoveListener(openVR.ofxOpenVRControllerEvent, this, &SceneManager::controllerEvent);

	}
};