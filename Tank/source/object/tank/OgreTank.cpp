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
	//setEntity(entity);
	mSceneNode->attachObject(entity);
	Ogre::Entity *barrel = ObjectFactory::createTankGunEntity(sceneManager);
	mBarrelSceneNode = mSceneNode->createChildSceneNode();
	mBarrelSceneNode->attachObject(barrel);
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

void OgreTank::yawBarrel(float degree) const {
	mBarrelSceneNode->yaw(Ogre::Radian(degree));
	Ogre::Degree yawDegree;
	mBarrelSceneNode->getOrientation().ToAngleAxis(yawDegree, Ogre::Vector3(0, 0, -1));
	if (yawDegree.valueDegrees() > 30) {
		float maxYawDegree = degree>0 ? 3.14/12 : -3.14/12;
		mBarrelSceneNode->setOrientation(Ogre::Math::Cos(Ogre::Radian(maxYawDegree)), 0, 
			Ogre::Math::Sin(Ogre::Radian(maxYawDegree)), 0);
	}
}

Ogre::Vector3 OgreTank::getBarrelWorldPosition() {
	return mSceneNode->getOrientation() * mBarrelSceneNode->getOrientation() * Ogre::Vector3(0, 0, -5);
}