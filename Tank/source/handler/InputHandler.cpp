#include "include\handler\InputHandler.h"

#include "Ogre.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>

#include <stdio.h>

InputHandler::InputHandler(Ogre::RenderWindow *renderWindow) : mRenderWindow(renderWindow) {
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	renderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mCurrentKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false /* not buffered */ ));
	mCurrentMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false /* not buffered */ ));
}

bool InputHandler::isKeyDown(OIS::KeyCode key) const {
	return mCurrentKeyboard->isKeyDown(key);
}

bool InputHandler::wasKeyDown(OIS::KeyCode key) const {
	return mOldKeys[key] != '\0';
}

bool InputHandler::isMouseDown(OIS::MouseButtonID mouse) const {
	return mCurrentMouse->getMouseState().buttonDown(mouse);
}

void InputHandler::think(Ogre::Real time) {
	mCurrentKeyboard->copyKeyStates(mOldKeys);
	mCurrentKeyboard->capture();
	mCurrentMouse->capture();
}

InputHandler::~InputHandler() {
	mInputManager->destroyInputObject(mCurrentKeyboard);
}

