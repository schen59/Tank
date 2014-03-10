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
	void setupViewPort();
	void setupWorld();
	void setupInputHandler();
	
	World *mWorld;
	TankCamera *mTankCamera;
	InputHandler *mInputHandler;
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::OverlaySystem *mOverlaySystem;
	bool mKeepGoing;
};

#endif