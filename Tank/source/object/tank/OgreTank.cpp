#include "include\object\tank\OgreTank.h"
#include "include\object\OgreObject.h"
#include "include\core\OgreWorld.h"
#include "include\factory\ObjectFactory.h"

#include "Ogre.h"
#include "OgreSceneManager.h"

OgreTank::OgreTank() {
	mIsExploded = false;
}

OgreTank::~OgreTank() {
}

void OgreTank::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createTankEntity(sceneManager);
	setEntity(entity);

	Ogre::Entity *entityGun = ObjectFactory::createTankGunEntity(sceneManager);
	mGunSceneNode = mSceneNode->createChildSceneNode();
	mGunSceneNode->attachObject(entityGun);
	//setEntity(entityGun);
}

void OgreTank::explode(OgreWorld *ogreWorld) {
	if (!mIsExploded) {
	    Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	    Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Explosion/Tank");
		mSceneNode->removeAndDestroyAllChildren();
	    mSceneNode->createChildSceneNode()->attachObject(particleSystem);
		mIsExploded = true;
	} 
}