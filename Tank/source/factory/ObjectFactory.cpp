#include "include\factory\ObjectFactory.h"
#include "include\tank\Tank.h"
#include "include\ground\Ground.h"
#include "include\wall\Wall.h"
#include "include\projectile\Projectile.h"

#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "btBulletDynamicsCommon.h"

Tank* ObjectFactory::createTank(btScalar mass, btVector3 &size) {
	Tank *tank = new Tank(mass, size);
	return tank;
}

Ground* ObjectFactory::createGround(btScalar mass, btVector3 &size) {
	Ground *ground = new Ground(mass, size);
	return ground;
}

Wall* ObjectFactory::createWall(btScalar mass, btVector3 &size) {
	Wall *wall = new Wall(mass, size);
	return wall;
}

Projectile* ObjectFactory::createProjectile(btScalar mass, btVector3 &size) {
	Projectile *projectile = new Projectile(mass, size);
	return projectile;
}

Ogre::Entity* ObjectFactory::createWallEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_X, 0);
    Ogre::MeshManager::getSingleton().createPlane("wall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 20, 20, 10, true, 1, 5, 1, Ogre::Vector3::UNIT_Y);
    Ogre::Entity* entity = sceneManager->createEntity("wall");
	entity->setMaterialName("Rockwall");
	return entity;
}

Ogre::Entity* ObjectFactory::createGroundEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entity = sceneManager->createEntity("ground");
	entity->setMaterialName("Rockwall");
	return entity;
}

Ogre::Entity* ObjectFactory::createTankEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = sceneManager->createEntity("Sphere.mesh");
	return entity;
}

Ogre::Entity* ObjectFactory::createProjectileEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = sceneManager->createEntity("Sphere.mesh");
	return entity;
}