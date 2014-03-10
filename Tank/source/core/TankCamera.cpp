#include "include\core\TankCamera.h"
#include "include\tank\Tank.h"
#include "include\tank\OgreTank.h"

#include "Ogre.h"

TankCamera::TankCamera(Ogre::Camera *camera) {
	mCamera = camera;
}

void TankCamera::follow(Tank *tank) {
	Ogre::SceneNode *parentSceneNode = tank->getOgreTank()->getSceneNode();
	Ogre::SceneNode *sceneNode = parentSceneNode->createChildSceneNode();
	sceneNode->attachObject(mCamera);
}

TankCamera::~TankCamera() {
}