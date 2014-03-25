#include "include\object\projectile\OgreShell.h"
#include "include\factory\ObjectFactory.h"
#include "include\core\OgreWorld.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"

OgreShell::OgreShell() {
}

OgreShell::~OgreShell() {
}

void OgreShell::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createProjectileEntity(sceneManager);
	setEntity(entity);
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Smoke");
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
}

void OgreShell::explode(OgreWorld *ogreWorld) {
	Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "Explosion");
    mSceneNode->removeAndDestroyAllChildren();
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
}