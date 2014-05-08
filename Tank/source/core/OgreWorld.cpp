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
	//Ogre::Entity *entity = object->getEntity();
	//sceneNode->detachObject(entity);
	//mSceneManager->destroyEntity(entity);
	mSceneManager->destroySceneNode(sceneNode);
	mObjects.erase(mObjects.find(object));
}

void OgreWorld::setLight(float timer) {

	if ((int)timer%100 >= 0 & (int)timer%100 < 10 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
	}
	else if ((int)timer%100 >= 10 & (int)timer%100 < 20 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.55, 0.55, 0.55));
	}
	else if ((int)timer%100 >= 20 & (int)timer%100 < 30 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.45, 0.45, 0.45));
	}
	else if ((int)timer%100 >= 30 & (int)timer%100 < 40){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.35, 0.35, 0.35));
	}
	else if ((int)timer%100 >= 40 & (int)timer%100 < 50){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
	}
	else if ((int)timer%100 >= 50 & (int)timer%100 < 60){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.15, 0.15, 0.15));
	}
	else if ((int)timer%100 >= 60 & (int)timer%100 < 70 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.35, 0.35, 0.35));
	}
	else if ((int)timer%100 >= 70 & (int)timer%100 < 80 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.45, 0.45, 0.45));
	}
	else if ((int)timer%100 >= 80 & (int)timer%100 < 90 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.55, 0.55, 0.55));
	}
	else if ((int)timer%100 >= 90 & (int)timer%100 < 100 ){
		mSceneManager->setAmbientLight(Ogre::ColourValue(0.65, 0.65, 0.65));
	}
}