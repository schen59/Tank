#include "include\manager\TankManager.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\PhysicsObject.h"
#include "include\core\TankCamera.h"
#include "include\core\World.h"
#include "include\handler\InputHandler.h"
#include "include\object\tank\Tank.h"
#include "include\core\MenuSystem.h"

#include "CEGUI\RendererModules\Ogre\Renderer.h"
#include "CEGUI\Scheme.h"
#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreOverlaySystem.h"
#include "OgreFontManager.h"
#include "Ogre.h"
#include "OgreFrameListener.h"


TankManager::TankManager(Ogre::Root *root, Ogre::RenderWindow *mainWindow) :mRoot(root), mWindow(mainWindow) {
	mKeepGoing = true;
	mWorld = NULL;
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
	setupCEGUI();
	setupMenuSystem();
	setupWorld();
}

void TankManager::setupCEGUI() {
	CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
}

void TankManager::setupMenuSystem() {
	mMenuSystem = new MenuSystem(mInputHandler);
}

void TankManager::setupInputHandler() {
	mInputHandler = new InputHandler(mWindow);
}

void TankManager::setupWorld() {
	mWorld = new World(mInputHandler);
	mWorld->setup(mSceneManager, btVector3(0, -10, 0));
	setupLight();
	setupCamera();
	setupViewPort();
	setupHUDCamera();
	setupHUDViewPort();
}

void TankManager::destroyWorld() {
	mSceneManager->destroyCamera("TankCamera");
	mSceneManager->destroyCamera("HUDCamera");
	mSceneManager->destroyAllBillboardSets();
	mSceneManager->destroyAllEntities();
	mSceneManager->getRootSceneNode()->removeAndDestroyAllChildren();
	mWindow->removeAllViewports();
	delete mWorld;
	mWorld = NULL;
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

void TankManager::setupHUDViewPort() {
	Ogre::Viewport* hudViewPort = mWindow->addViewport(mHUDCamera, 100, 0, 0.7, 0.3, 0.3);
	hudViewPort->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	hudViewPort->setOverlaysEnabled(false);
	mHUDCamera->setAspectRatio(Ogre::Real(hudViewPort->getActualWidth()) / Ogre::Real(hudViewPort->getActualHeight()));
}

void TankManager::setupCamera() {
	Ogre::Camera *camera = mSceneManager->createCamera("TankCamera");
	camera->setNearClipDistance(5);
	camera->setFarClipDistance(5000);
	camera->setPosition(Ogre::Vector3(0, 5, 10));
	camera->setOrientation(Ogre::Quaternion(0.98, -0.17, 0, 0));
	mTankCamera = new TankCamera(camera);
	mTankCamera->follow(mWorld->getHumanPlayer());
}

void TankManager::setupHUDCamera() {
	mHUDCamera = mSceneManager->createCamera("HUDCamera");
	mHUDCamera->pitch(Ogre::Radian(-1.57));
	mHUDCamera->setNearClipDistance(5);
	mHUDCamera->setFarClipDistance(250);
	mHUDCamera->setPosition(Ogre::Vector3(0, 250, 0));
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
	destroyWorld();
}

bool TankManager::frameStarted(const Ogre::FrameEvent &event) {
	Ogre::Real time = event.timeSinceLastFrame;
	if (time > 0.5) {
		time = 0.5;
	}
	
	think(time);
	
	return mKeepGoing;
}

void TankManager::toggleMenuSystem() {
	if (mMenuSystem->isActive()) {
		mMenuSystem->deactivate();
	} else {
		mMenuSystem->activate();
	}
}

void TankManager::processMenuCommand() {
	if (mMenuSystem->getCommand() == Properties::MenuCommand::QUIT) {
		mKeepGoing = false;
	}
	if (mMenuSystem->getCommand() == Properties::MenuCommand::NEWGAME_EASY) {
	    mMenuSystem->deactivate();
		if (mWorld != NULL) {
			destroyWorld();
		}
		if (mWorld == NULL) {
		    setupWorld();
		}
	}
}

void TankManager::think(const Ogre::Real &time) {
	mInputHandler->think(time);
	mMenuSystem->think(time);
	if (mMenuSystem->isActive()) {
	    processMenuCommand();
	}
	if (!mMenuSystem->isActive() && mWorld != NULL) {
	    mWorld->think(time);
	}
	if (mWindow->isClosed() || mInputHandler->isKeyDown(OIS::KC_ESCAPE)) {
		mKeepGoing = false;
	}
	if (!mInputHandler->isKeyDown(OIS::KC_Q) && mInputHandler->wasKeyDown(OIS::KC_Q)) {
		toggleMenuSystem();
	}
}