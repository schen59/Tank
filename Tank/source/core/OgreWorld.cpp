#include "include\core\OgreWorld.h"
#include "include\object\OgreObject.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreSceneNode.h"
#include "Ogre.h"
#include <set>

OgreWorld::OgreWorld(Ogre::SceneManager *sceneManager) {
	mSceneManager = sceneManager;
}

OgreWorld::~OgreWorld() {
	destroyObjects();
}

void OgreWorld::destroyObjects() {
	std::set<OgreObject*>::iterator it=mObjects.begin();
	while (it != mObjects.end()) {
		OgreObject *object = *it;
		it++;
		delete object;
	}
	mObjects.clear();
}

void OgreWorld::addObject(OgreObject *object, Ogre::Quaternion orientation, Ogre::Vector3 position) {
	object->addToScene(mSceneManager, orientation, position);
	mObjects.insert(object);
}

void OgreWorld::removeObject(OgreObject *object) {
	Ogre::SceneNode *sceneNode = object->getSceneNode();
	sceneNode->removeAndDestroyAllChildren();
	Ogre::Entity *entity = object->getEntity();
	sceneNode->detachObject(entity);
	mSceneManager->destroyEntity(entity);
	mObjects.erase(mObjects.find(object));
}
