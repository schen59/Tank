#include "include\manager\TankManager.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\PhysicsObject.h"
#include "include\core\TankCamera.h"
#include "include\core\World.h"
#include "include\handler\InputHandler.h"
#include "include\object\tank\Tank.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreOverlaySystem.h"
#include "OgreFontManager.h"
#include "Ogre.h"
#include "OgreFrameListener.h"


TankManager::TankManager(Ogre::Root *root, Ogre::RenderWindow *mainWindow) :mRoot(root), mWindow(mainWindow) {
	mKeepGoing = true;
}

void TankManager::setupOverlaySystem() {
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneManager->addRenderQueueListener(mOverlaySystem);
}

void TankManager::setup() {
	setupSceneManager();
	setupOverlaySystem();
	setupResourceGroup();
	setupInputHandler();
	setupWorld();
	setupLight();
	setupCamera();
	setupViewPort();
}

void TankManager::setupInputHandler() {
	mInputHandler = new InputHandler(mWindow);
}

void TankManager::setupWorld() {
	mWorld = new World(mInputHandler);
	mWorld->setup(mSceneManager, btVector3(0, -10, 0));
}

void TankManager::setupLight() {
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
}

void TankManager::setupViewPort() {
	Ogre::Camera *camera = mTankCamera->getCamera();
	Ogre::Viewport* viewPort = mWindow->addViewport(camera);
	viewPort->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
	camera->setAspectRatio(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));
}

void TankManager::setupCamera() {
	Ogre::Camera *camera = mSceneManager->createCamera("TankCamera");
	camera->setNearClipDistance(5);
	camera->setFarClipDistance(5000);
	camera->setPosition(Ogre::Vector3(0, 3, 3));
	camera->setOrientation(Ogre::Quaternion(0.98, -0.17, 0, 0));
	mTankCamera = new TankCamera(camera);
	mTankCamera->follow(mWorld->getHumanPlayer());
}

void TankManager::setupSceneManager() {
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "TankSceneManager");
}

void TankManager::setupResourceGroup() {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();  
	Ogre::ResourceManager::ResourceMapIterator iter = Ogre::FontManager::getSingleton().getResourceIterator();
	while (iter.hasMoreElements()) { 
		iter.getNext()->load(); 
	}
}

TankManager::~TankManager() {
	delete mTankCamera;
	mSceneManager->destroyCamera("TankCamera");
	mSceneManager->destroyAllEntities();
	mSceneManager->getRootSceneNode()->removeAndDestroyAllChildren();
	mRoot->destroySceneManager(mSceneManager);
	delete mWorld;
}

bool TankManager::frameStarted(const Ogre::FrameEvent &event) {
	Ogre::Real time = event.timeSinceLastFrame;
	if (time > 0.5) {
		time = 0.5;
	}
	
	think(time);
	
	return mKeepGoing;
}

void TankManager::think(const Ogre::Real &time) {
	mInputHandler->think(time);
	mWorld->think(time);
	if (mWindow->isClosed() || mInputHandler->isKeyDown(OIS::KC_ESCAPE)) {
		mKeepGoing = false;
	}
}