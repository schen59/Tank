#include "include\core\TankCamera.h"
#include "include\object\AbstractObject.h"

#include "Ogre.h"

TankCamera::TankCamera(Ogre::Camera *camera) {
	mCamera = camera;
}

void TankCamera::follow(AbstractObject *object) {
	Ogre::SceneNode *parentSceneNode = object->getSceneNode();
	Ogre::SceneNode *sceneNode = parentSceneNode->createChildSceneNode();
	sceneNode->attachObject(mCamera);
}

TankCamera::~TankCamera() {
}