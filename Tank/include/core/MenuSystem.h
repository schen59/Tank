#ifndef __MenuSystem_h_
#define __MenuSystem_h_

#include "include\common\Properties.h"
#include "CEGUI\RendererModules\Ogre\Renderer.h"
#include "OIS\OIS.h"

class InputHandler;

class MenuSystem {
public:
	MenuSystem(InputHandler *inputHandler);
	~MenuSystem();
	void think(float time);
	bool isActive() const;
	void activate();
	void deactivate();
	Properties::MenuCommand getCommand() const;

private:
	void initialize();
	void injectMouseMove(const OIS::MouseState &mouseState);
	void injectMouseButtonDown(OIS::MouseButtonID mouseButton);
	void injectMouseClicked(OIS::MouseButtonID mouseButton);
	bool onQuit(const CEGUI::EventArgs& eventArgs);
	bool onNewEasyGame(const CEGUI::EventArgs& eventArgs);

	InputHandler *mInputHandler;
	CEGUI::OgreRenderer *mRenderer;
	Properties::MenuCommand mCommand;
	bool mIsActive;
};

#endif