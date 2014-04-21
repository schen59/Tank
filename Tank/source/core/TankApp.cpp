#include "include\core\TankApp.h"
#include "include\manager\TankManager.h"
#include "include\core\MenuSystem.h"

#include "Ogre.h"

TankApp::TankApp() {
	mResourcePath = "";
	mTankManager = NULL;
	mRoot = NULL;
}

TankApp::~TankApp() {
	if (mTankManager != NULL) {
		delete mTankManager;
	}
	if (mRoot != NULL) {
		delete mRoot;
	}
}

void TankApp::go() {
	if (setup()) {
        mRoot->startRendering();
	}
}

bool TankApp::setup() {
	setupRoot();
	setupResources();
	bool carryOn = configure();
	if (!carryOn) {
		return false;
	}
	setupTankManager();
	return true;
}

void TankApp::setupTankManager() {
	mTankManager = new TankManager(mRoot, mWindow);
	mTankManager->setup();
	mRoot->addFrameListener(mTankManager);
}

bool TankApp::configure() {
	if(mRoot->showConfigDialog()) {
        mWindow = mRoot->initialise(true);
        return true;
    } else {
        return false;
    }
}

void TankApp::setupRoot() {
	Ogre::String pluginsPath;
	Ogre::String configPath;
    // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB

#if OGRE_DEBUG_MODE == 1
	pluginsPath = mResourcePath + "plugins_d.cfg";
	configPath = mResourcePath + "ogre_d.cfg";
#else
	pluginsPath = mResourcePath + "plugins.cfg";
	configPath = mResourcePath + "ogre.cfg";

#endif

#endif
	
    mRoot = new Ogre::Root(pluginsPath, configPath, mResourcePath + "Ogre.log");
}

void TankApp::setupResources() {
	Ogre::ConfigFile cf;
#if OGRE_DEBUG_MODE == 1
    cf.load(mResourcePath + "resources_d.cfg");
#else
	cf.load(mResourcePath + "resources.cfg");
#endif
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}