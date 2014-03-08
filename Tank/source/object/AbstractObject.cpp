#include "include\object\AbstractObject.h"

#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "Ogre.h"

AbstractObject::AbstractObject() {
}

void AbstractObject::addToScene(Ogre::SceneNode *parentSceneNode) {
	mSceneNode = parentSceneNode->createChildSceneNode();
	mSceneNode->attachObject(mEntity);
}

void AbstractObject::setScale(Ogre::Vector3 scale) {
	mSceneNode->setScale(scale);
}

void AbstractObject::setPosition(Ogre::Vector3 position) {
	mSceneNode->setPosition(position);
}

Ogre::Quaternion AbstractObject::getOrientation() const {
	return mSceneNode->getOrientation();
}

Ogre::Vector3 AbstractObject::getDirection() const {
	return getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
}

AbstractObject::~AbstractObject() {
}