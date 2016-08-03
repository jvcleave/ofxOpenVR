#pragma once

#define STRINGIFY(A) #A
#include "DrawingScene.h"
#include "VideoScene.h"
#include "BoxScene.h"

class SceneManager
{
public:

	vector<BaseScene*> scenes;
	BaseScene* currentScene;
	ofxOpenVR openVR;

	bool bShowHelp;
	std::ostringstream _strHelp;
	int currentSceneIndex;
	SceneManager()
	{
		bShowHelp = false;
		_strHelp.str("");
		currentScene = NULL;
		currentSceneIndex = -1;
	}

	void loadNextScene()
	{
		if (currentSceneIndex + 1 < scenes.size())
		{
			currentSceneIndex++;
		}
		else
		{
			currentSceneIndex = 0;
		}
		currentScene = scenes[currentSceneIndex];
	}
	void setup()
	{
		// We need to pass the method we want ofxOpenVR to call when rending the scene
		openVR.setup(std::bind(&SceneManager::render, this, std::placeholders::_1));
		openVR.setDrawControllers(true);
		openVR.setRenderModelForTrackedDevices(true);
		ofAddListener(openVR.ofxOpenVRControllerEvent, this, &SceneManager::controllerEvent);

		

		BoxScene* boxScene = new BoxScene();
		boxScene->setup(&openVR);
		scenes.push_back(boxScene);

		VideoScene* videoScene = new VideoScene();
		videoScene->setup(&openVR);
		scenes.push_back(videoScene);

		DrawingScene* drawingScene = new DrawingScene();
		drawingScene->setup(&openVR);
		scenes.push_back(drawingScene);

		



		currentSceneIndex = 0;
		currentScene = scenes[currentSceneIndex];
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

		if (bShowHelp && currentScene) {
		
			ofDrawBitmapStringHighlight(currentScene->getHelpInfo(), ofPoint(10.0f, 20.0f), ofColor(ofColor::black, 100.0f));
		}
	}

	void onKeyPressed(int key)
	{
		switch (key)
		{
			case 'h':
			{
				bShowHelp = !bShowHelp;
				break;
			}
			case 'm': {

				openVR.setRenderModelForTrackedDevices(!openVR.getRenderModelForTrackedDevices());
				break;
			}
				
			default:
			{
				if (currentScene)
				{
					currentScene->onKeyPressed(key);
				}
				break;
			}
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
			switch (args.controllerRole)
			{
			case ControllerRole::Left:
			{
				switch (args.buttonType)
				{
				case ButtonType::ButtonTrigger:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onLeftButtonPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onLeftButtonRelease();
						}
					}
					break;
				}
				case ButtonType::ButtonTouchpad:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onLeftTouchPadPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onLeftTouchPadRelease();
						}
					}
					break;
				}
				case ButtonType::ButtonGrip:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onLeftGripPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onLeftGripRelease();
						}
					}
					break;
				}
				}
				break;
			}
			case ControllerRole::Right:
			{
				switch (args.buttonType)
				{
				case ButtonType::ButtonTrigger:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onRightButtonPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onRightButtonRelease();
						}
					}
					break;
				}
				case ButtonType::ButtonTouchpad:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onRightTouchPadPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onRightTouchPadRelease();
						}
					}
					break;
				}
				case ButtonType::ButtonGrip:
				{
					if (args.eventType == EventType::ButtonPress)
					{
						currentScene->onRightGripPress();
					}
					else
					{
						if (args.eventType == EventType::ButtonUnpress)
						{
							currentScene->onRightGripRelease();
						}
					}
					break;
				}
				}
				break;
			}
			}
		}
	}
	void exit()
	{
		ofRemoveListener(openVR.ofxOpenVRControllerEvent, this, &SceneManager::controllerEvent);

	}
};