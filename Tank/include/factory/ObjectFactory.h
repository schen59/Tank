#ifndef __ObjectFactory_h_
#define __ObjectFactory_h_

#include "btBulletDynamicsCommon.h"

namespace Ogre {
	class SceneManager;
	class Entity;
}

class Tank;
class Ground;
class Wall;
class Projectile;

class ObjectFactory {
public:
	static Tank* createTank(btScalar mass, btVector3 &size);
	static Wall* createWall(btScalar mass, btVector3 &size);
	static Ground* createGround(btScalar mass, btVector3 &size);
	static Projectile* createProjectile(btScalar mass, btVector3 &size);
	static Ogre::Entity* createWallEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createTankEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createGroundEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createProjectileEntity(Ogre::SceneManager *sceneManager);

private:

	ObjectFactory();
	~ObjectFactory();
};

#endif