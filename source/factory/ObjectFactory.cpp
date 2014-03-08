#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"

Ground* ObjectFactory::createGround(Ogre::SceneManager *sceneManager) {
	Ground *ground = new Ground(sceneManager);
	ground->load();
	return ground;
}

Wall* ObjectFactory::createWall(Ogre::SceneManager *sceneManager) {
	Wall *wall = new Wall(sceneManager);
	wall->load();
	return wall;
}

Tank* ObjectFactory::createTank(Ogre::SceneManager *sceneManager) {
	Tank *tank = new Tank(sceneManager);
	tank->load();
	return tank;
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