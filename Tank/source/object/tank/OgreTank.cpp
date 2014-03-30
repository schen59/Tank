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
	Ogre::SceneNode *headNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	setEntity(entity);
	//headNode->attachObject(entity);
	//Ogre::Entity *entityGun = ObjectFactory::createTankGunEntity(sceneManager);
	//Ogre::SceneNode *headNodeGun = headNode->createChildSceneNode();
	//headNodeGun->attachObject(entityGun);
	
	//setEntity(entityGun);
}
/*
Ogre::Entity *pBody = mSceneManager->createEntity("Body.mesh");mTankBodyNode = mSceneManager->getRootSceneNode()->createChildSceneNode();mTankBodyNode->attachObject(pBody);
Ogre::Entity *pTurret = mSceneManager->createEntity("Turret.mesh");mTankTurretNode = mTankBodyNode->createChildSceneNode();mTankTurretNode->attachObject(pTurret);
*/
void OgreTank::explode(OgreWorld *ogreWorld) {
	if (!mIsExploded) {
	    Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	    Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Explosion/Tank");
		mSceneNode->removeAndDestroyAllChildren();
	    mSceneNode->createChildSceneNode()->attachObject(particleSystem);
		mIsExploded = true;
	} 
}