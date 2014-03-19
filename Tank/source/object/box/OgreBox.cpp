#include "include\object\box\OgreBox.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"

OgreBox::OgreBox() {
}

OgreBox::~OgreBox() {
}

void OgreBox::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createBoxEntity(sceneManager);
	setEntity(entity);
}
