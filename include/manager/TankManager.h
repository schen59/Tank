#ifndef __TankManager_h_
#define __TankManager_h_

#include "include\core\World.h"
#include "include\core\TankCamera.h"
#include "include\handler\InputHandler.h"
#include "include\core\PhysicsWorld.h"

#include "Ogre.h"
#include "OgreFrameListener.h"

namespace Ogre {
	class FrameListener;
	class Root;
	class RenderWindow;
	class SceneManager;
	class OverlaySystem;
}

class World;
class TankCamera;
class InputHandler;
class PhysicsWorld;

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
	void setupPhysicsWorld();

	World *mWorld;
	PhysicsWorld *mPhysicsWorld;
	TankCamera *mTankCamera;
	InputHandler *mInputHandler;
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::OverlaySystem *mOverlaySystem;
	bool mKeepGoing;
};

#endif