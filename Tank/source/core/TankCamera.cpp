#include "include\core\TankCamera.h"
#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"

#include "Ogre.h"

TankCamera::TankCamera(Ogre::Camera *camera) {
	mCamera = camera;
}

void TankCamera::follow(AbstractObject *object) {
	Ogre::SceneNode *parentSceneNode = object->getOgreObject()->getSceneNode();
	Ogre::SceneNode *sceneNode = parentSceneNode->createChildSceneNode();
	sceneNode->setOrientation(object->getOgreObject()->getOrientation());
	sceneNode->attachObject(mCamera);
}

TankCamera::~TankCamera() {
}