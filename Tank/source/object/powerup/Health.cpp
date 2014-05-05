#include "include\object\powerup\Health.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"

Health::Health() {
}

Health::~Health() {
}

void Health::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createHealthPowerEntity(sceneManager);
	mSceneNode->attachObject(entity);
}