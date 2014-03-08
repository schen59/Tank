#ifndef __ObjectFactory_h_
#define __ObjectFactory_h_

#include "include\object\Ground.h"
#include "include\object\Wall.h"
#include "include\object\Tank.h"

namespace Ogre {
	class SceneManager;
	class Entity;
}

class Ground;
class Wall;
class Tank;

class ObjectFactory {
public:
	static Ground* createGround(Ogre::SceneManager *sceneManager);
	static Wall* createWall(Ogre::SceneManager *sceneManager);
	static Tank* createTank(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createWallEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createGroundEntity(Ogre::SceneManager *sceneManager);

private:

	ObjectFactory();
	~ObjectFactory();
};

#endif