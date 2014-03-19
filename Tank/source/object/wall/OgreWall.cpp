#include "include\object\wall\OgreWall.h"
#include "include\object\OgreObject.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"

OgreWall::OgreWall() {
}

OgreWall::~OgreWall() {
}

void OgreWall::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createWallEntity(sceneManager);
	setEntity(entity);
}