#include "include\object\Ground.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgrePlane.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreResourceGroupManager.h"
#include "Ogre.h"

Ground::Ground(Ogre::SceneManager *sceneManager) {
	mSceneManager = sceneManager;
}

Ground::~Ground() {
}

void Ground::load() {
	Ogre::Entity *entity = ObjectFactory::createGroundEntity(mSceneManager);
	setEntity(entity);
}