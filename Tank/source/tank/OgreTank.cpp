#include "include\tank\OgreTank.h"
#include "include\object\OgreObject.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"

OgreTank::OgreTank() {
}

OgreTank::~OgreTank() {
}

void OgreTank::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createTankEntity(sceneManager);
	setEntity(entity);
}