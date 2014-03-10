#include "include\projectile\OgreProjectile.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreEntity.h"

OgreProjectile::OgreProjectile() {
}

OgreProjectile::~OgreProjectile() {
}

void OgreProjectile::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createProjectileEntity(sceneManager);
	setEntity(entity);
}