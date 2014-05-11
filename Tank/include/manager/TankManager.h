#ifndef __TankManager_h_
#define __TankManager_h_

#include "Ogre.h"
#include "OgreFrameListener.h"

namespace Ogre {
	class FrameListener;
	class Root;
	class RenderWindow;
	class SceneManager;
	class FrameEvent;
	class OverlaySystem;
}

class World;
class TankCamera;
class InputHandler;
class MenuSystem;

class TankManager : public Ogre::FrameListener {
public:
	TankManager(Ogre::Root *root, Ogre::RenderWindow *mainWindow);
	~TankManager();
	bool frameStarted(const Ogre::FrameEvent &event);
	void setup();

private:
	void setupSceneManager();
	void setupOverlaySystem();
	void setupResourceGroup();
	void think(const Ogre::Real &time);
	void setupLight();
	void setupCamera();
	void setupHUDCamera();
	void setupHUDViewPort();
	void setupViewPort();
	void setupWorld(bool isHard);
	void setupInputHandler();
	void setupMenuSystem();
	void setupCEGUI();
	void toggleMenuSystem();
	void destroyWorld();
	void processMenuCommand();
	
	World *mWorld;
	TankCamera *mTankCamera;
	Ogre::Camera *mHUDCamera;
	InputHandler *mInputHandler;
	MenuSystem *mMenuSystem;
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::OverlaySystem *mOverlaySystem;
	bool mKeepGoing;
};

#endif