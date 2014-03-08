#include "include\object\Tank.h"
#include "include\object\AbstractObject.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"

Tank::Tank(Ogre::SceneManager *sceneManager) {
	mSceneManager = sceneManager;
	mSpeed = 20;
}

void Tank::load() {
	Ogre::Entity *entity = mSceneManager->createEntity("Sphere.mesh");
	setEntity(entity);
}

void Tank::moveForward(Ogre::Real time) {
	Ogre::SceneNode *sceneNode = getSceneNode();
	Ogre::Vector3 direction = getDirection();
	sceneNode->translate(mSpeed * time * direction);
}

void Tank::moveBackward(Ogre::Real time) {
	Ogre::SceneNode *sceneNode = getSceneNode();
	Ogre::Vector3 direction = getDirection();
	sceneNode->translate(-mSpeed * time * direction);
}

void Tank::yaw(Ogre::Real time) {
	Ogre::SceneNode *sceneNode = getSceneNode();
	sceneNode->yaw(Ogre::Radian(1 * time));
}

Tank::~Tank() {
}