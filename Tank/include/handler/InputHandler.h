#ifndef __InputHandler_h_
#define __InputHandler_h_

#include <ois/ois.h>
#include "Ogre.h"

namespace Ogre {
	class RenderWindow;
}

class InputHandler {
public:
	InputHandler(Ogre::RenderWindow* renderWindow);
	~InputHandler();
	void think(Ogre::Real time);
	bool isKeyDown(OIS::KeyCode key) const;
	bool wasKeyDown(OIS::KeyCode key) const;
	bool isMouseDown(OIS::MouseButtonID mouse) const;
	bool isMouseMoveLeft() const;
	bool isMouseMoveRight() const;
	bool isMouseMoveUp() const;
	bool isMouseMoveDown() const;
	bool wasMouseDown(OIS::MouseButtonID mouse) const;

protected:
	OIS::InputManager* mInputManager;
	Ogre::RenderWindow *mRenderWindow;
	OIS::Keyboard *mPreviousKeyboard;
	OIS::Keyboard *mCurrentKeyboard;
	OIS::Mouse *mCurrentMouse;
	char mOldKeys[256];
};

#endif