#include "include\object\projectile\OgreMissile.h"
#include "include\factory\ObjectFactory.h"
#include "include\core\OgreWorld.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"

OgreMissile::OgreMissile() {
	mIsExploded = false;
}

OgreMissile::~OgreMissile() {
}

void OgreMissile::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createMissileEntity(sceneManager);
	setEntity(entity);
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "SmokeMissile");
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
}

void OgreMissile::explode(OgreWorld *ogreWorld) {
	if (!mIsExploded) {
	    Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	    Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "ExplosionMissile");
		mSceneNode->removeAndDestroyAllChildren();
	    mSceneNode->createChildSceneNode()->attachObject(particleSystem);
		mIsExploded = true;
	} 
}