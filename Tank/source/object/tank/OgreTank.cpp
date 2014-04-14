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
	loadBody(sceneManager);
	loadBarrel(sceneManager);
	loadHealthBar(sceneManager);
}

void OgreTank::loadBody(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createTankEntity(sceneManager);
	mSceneNode->attachObject(entity);
}

void OgreTank::loadBarrel(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *barrel = ObjectFactory::createTankGunEntity(sceneManager);
	mBarrelSceneNode = mSceneNode->createChildSceneNode();
	mBarrelSceneNode->attachObject(barrel);
}

void OgreTank::loadHealthBar(Ogre::SceneManager *sceneManager) {
	Ogre::BillboardSet *billBoardSet = ObjectFactory::createBillboardSet(sceneManager);
	mHealthBar = billBoardSet->createBillboard(0, 1, 3);
	mHealthBar->setDimensions(3, 0.25);
	mSceneNode->attachObject(billBoardSet);
}

void OgreTank::updateHealthBar(float health) {
	mHealthBar->setDimensions(health, 0.25);
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

void OgreTank::pitchBarrel(float degree) const {
	mBarrelSceneNode->pitch(Ogre::Radian(degree));
	Ogre::Degree pitchDegree;
	mBarrelSceneNode->getOrientation().ToAngleAxis(pitchDegree, Ogre::Vector3(0, 0, -1));
	if (pitchDegree.valueDegrees() > 5) {
		float maxPitchDegree = 2.5;
		mBarrelSceneNode->setOrientation(Ogre::Math::Cos(Ogre::Degree(maxPitchDegree)),  
			Ogre::Math::Sin(Ogre::Degree(maxPitchDegree)), 0, 0);
	}
}

Ogre::Vector3 OgreTank::getBarrelWorldPosition() {
	return mSceneNode->getOrientation() * mBarrelSceneNode->getOrientation() * Ogre::Vector3(0, 0, -5);
}