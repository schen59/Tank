#include "include\object\Wall.h"
#include "include\object\AbstractObject.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"

Wall::Wall(Ogre::SceneManager *sceneManager) {
	mSceneManager = sceneManager;
}

void Wall::load() {
	Ogre::Entity *entity = ObjectFactory::createWallEntity(mSceneManager);
	setEntity(entity);
}

Wall::~Wall() {
}