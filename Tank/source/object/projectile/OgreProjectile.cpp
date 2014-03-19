#include "include\object\projectile\OgreProjectile.h"
#include "include\factory\ObjectFactory.h"
#include "include\core\OgreWorld.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"

OgreProjectile::OgreProjectile() {
	mIsExploded = false;
}

OgreProjectile::~OgreProjectile() {
}

void OgreProjectile::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createProjectileEntity(sceneManager);
	setEntity(entity);
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Smoke");
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
}

void OgreProjectile::explode(OgreWorld *ogreWorld) {
	if (!mIsExploded) {
	    Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	    Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Explosion");
		mSceneNode->removeAndDestroyAllChildren();
	    mSceneNode->createChildSceneNode()->attachObject(particleSystem);
		mIsExploded = true;
	} 
}