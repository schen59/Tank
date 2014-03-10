#include "include\object\OgreObject.h"

#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "Ogre.h"

OgreObject::OgreObject() {
}

void OgreObject::addToScene(Ogre::SceneManager *sceneManager, Ogre::Quaternion orientation, Ogre::Vector3 position) {
	load(sceneManager);
	mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mEntity);
	mSceneNode->setOrientation(orientation);
	mSceneNode->setPosition(position);
}

void OgreObject::setScale(Ogre::Vector3 scale) {
	mSceneNode->setScale(scale);
}

void OgreObject::setPosition(Ogre::Vector3 position) {
	mSceneNode->setPosition(position);
}

Ogre::Quaternion OgreObject::getOrientation() const {
	return mSceneNode->getOrientation();
}

Ogre::Vector3 OgreObject::getDirection() const {
	return getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
}

OgreObject::~OgreObject() {
}