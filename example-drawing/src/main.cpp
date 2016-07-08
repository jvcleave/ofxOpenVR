#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofGLWindowSettings settings;
	settings.setGLVersion(4, 1);
	settings.width = 1280;
	settings.height = 720;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
