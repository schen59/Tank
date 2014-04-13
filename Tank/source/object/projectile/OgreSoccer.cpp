#include "include\object\projectile\OgreSoccer.h"
#include "include\factory\ObjectFactory.h"
#include "include\core\OgreWorld.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreParticleSystem.h"

OgreSoccer::OgreSoccer() {
}

OgreSoccer::~OgreSoccer() {
}

void OgreSoccer::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createSoccerEntity(sceneManager);
	//setEntity(entity);
	mSceneNode->createChildSceneNode()->attachObject(entity);
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "SmokeSoccer");
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
	mSceneNode->scale(.5, .5, .5);
}

void OgreSoccer::explode(OgreWorld *ogreWorld) {
	Ogre::SceneManager *sceneManager = ogreWorld->getSceneManager();
	Ogre::ParticleSystem *particleSystem = ObjectFactory::createParticleSystem(sceneManager, "ExplosionSoccer");
    mSceneNode->removeAndDestroyAllChildren();
	mSceneNode->createChildSceneNode()->attachObject(particleSystem);
}