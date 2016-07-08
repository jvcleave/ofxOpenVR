#pragma once

class ControllerListener
{

public:
	virtual void onLeftButtonPress() {};
	virtual void onLeftButtonRelease() {};
	virtual void onLeftTouchPadPress() {};
	virtual void onLeftTouchPadRelease() {};
	virtual void onLeftGripPress() {};
	virtual void onLeftGripRelease() {};
	virtual void onRightButtonPress() {};
	virtual void onRightButtonRelease() {};
	virtual void onRightTouchPadPress() {};
	virtual void onRightTouchPadRelease() {};
	virtual void onRightGripPress() {};
	virtual void onRightGripRelease() {};
};