#include "include\object\ground\OgreGround.h"
#include "include\object\OgreObject.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"

OgreGround::OgreGround() {
}

OgreGround::~OgreGround() {
}

void OgreGround::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createGroundEntity(sceneManager);
	//setEntity(entity);
	mSceneNode->createChildSceneNode()->attachObject(entity);
}