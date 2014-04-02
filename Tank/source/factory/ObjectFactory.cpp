#include "include\factory\ObjectFactory.h"
#include "include\object\tank\Tank.h"
#include "include\object\ground\Ground.h"
#include "include\object\wall\Wall.h"
#include "include\object\projectile\Shell.h"
#include "include\object\projectile\Missile.h"
#include "include\object\projectile\Soccer.h"
#include "include\object\box\Box.h"

#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "Ogre.h"
#include "OgreParticleSystem.h"
#include "btBulletDynamicsCommon.h"

int ObjectFactory::objectId = 1;

Tank* ObjectFactory::createTank(btScalar mass, btVector3 &size) {
	Tank *tank = new Tank(mass, size);
	return tank;
}

Tank* ObjectFactory::createTankGun(btScalar mass, btVector3 &size) {
	Tank *tankGun = new Tank(mass, size);
	return tankGun;
}

Ground* ObjectFactory::createGround(btScalar mass, btVector3 &size) {
	Ground *ground = new Ground(mass, size);
	return ground;
}

Wall* ObjectFactory::createWall(btScalar mass, btVector3 &size) {
	Wall *wall = new Wall(mass, size);
	return wall;
}

Shell* ObjectFactory::createShell(btScalar mass, btVector3 &size) {
	Shell *shell = new Shell(mass, size);
	return shell;
}

Missile* ObjectFactory::createMissile(btScalar mass, btVector3 &size) {
	Missile *missile = new Missile(mass, size);
	return missile;
}

Soccer* ObjectFactory::createSoccer(btScalar mass, btVector3 &size) {
	Soccer *soccer= new Soccer(mass, size);
	return soccer;
}

Box* ObjectFactory::createBox(btScalar mass, btVector3 &size) {
	Box *box = new Box(mass, size);
	return box;
}

Ogre::String ObjectFactory::createUniqueObjectName(Ogre::String name) {
	return name + Ogre::StringConverter::toString(objectId++);
}

Ogre::Entity* ObjectFactory::createWallEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_X, 0);
	Ogre::String name = createUniqueObjectName("wall");
    Ogre::MeshManager::getSingleton().createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 20, 20, 10, true, 1, 5, 1, Ogre::Vector3::UNIT_Y);
    Ogre::Entity* entity = sceneManager->createEntity(name);
	entity->setMaterialName("Rockwall");
	return entity;
}

Ogre::Entity* ObjectFactory::createGroundEntity(Ogre::SceneManager *sceneManager) {
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::String name = createUniqueObjectName("ground");
    Ogre::MeshManager::getSingleton().createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entity = sceneManager->createEntity(name);
	entity->setMaterialName("Rockwall");
	return entity;
}
// example for adding a root node and child
/*  
Ogre::Entity *pBody = mSceneManager->createEntity("Body.mesh");
mTankBodyNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
mTankBodyNode->attachObject(pBody);
Ogre::Entity *pTurret = mSceneManager->createEntity("Turret.mesh");
mTankTurretNode = mTankBodyNode->createChildSceneNode();
mTankTurretNode->attachObject(pTurret);

*/
Ogre::Entity* ObjectFactory::createTankEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("tank");
	Ogre::Entity *entity = sceneManager->createEntity(name, "Tank.mesh");
	Ogre::SceneNode *headNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	return entity;
}

Ogre::Entity* ObjectFactory::createTankGunEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("tankGun");
	Ogre::Entity *entity = sceneManager->createEntity(name, "TankGun.mesh");
	return entity;
}

Ogre::Entity* ObjectFactory::createBoxEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("box");
	Ogre::Entity *entity = sceneManager->createEntity(name, "Box.mesh");
	return entity;
}


Ogre::Entity* ObjectFactory::createProjectileEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("projectile");
	Ogre::Entity *entity = sceneManager->createEntity(name, "Shell.mesh");
	return entity;
}

Ogre::Entity* ObjectFactory::createMissileEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("missile");
	Ogre::Entity *entity = sceneManager->createEntity(name, "missile.mesh");
	return entity;
}

Ogre::Entity* ObjectFactory::createSoccerEntity(Ogre::SceneManager *sceneManager) {
	Ogre::String name = createUniqueObjectName("soccer");
	Ogre::Entity *entity = sceneManager->createEntity(name, "soccer.mesh");
	return entity;
}

Ogre::ParticleSystem* ObjectFactory::createParticleSystem(Ogre::SceneManager *sceneManager, Ogre::String particleName) {
	Ogre::String name = createUniqueObjectName(particleName);
	Ogre::ParticleSystem *particleSystem = sceneManager->createParticleSystem(name, particleName);
	return particleSystem;
}