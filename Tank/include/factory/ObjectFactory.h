#ifndef __ObjectFactory_h_
#define __ObjectFactory_h_

#include "btBulletDynamicsCommon.h"
#include "Ogre.h"

namespace Ogre {
	class SceneManager;
	class Entity;
	class ParticleSystem;
	class BillboardSet;
}

class Health;
class Tank;
class Ground;
class Wall;
class Shell;
class Missile;
class Soccer;
class Box;

class ObjectFactory {
public:
	static int objectId;
	static Tank* createTank(btScalar mass, btVector3 &size);
	static Tank* createTankGun(btScalar mass, btVector3 &size);
	static Wall* createWall(btScalar mass, btVector3 &size);
	static Ground* createGround(btScalar mass, btVector3 &size);
	static Shell* createShell(btScalar mass, btVector3 &size);
	static Missile* createMissile(btScalar mass, btVector3 &size);
	static Soccer* createSoccer(btScalar mass, btVector3 &size);
	static Box* createBox(btScalar mass, btVector3 &size);
	static Health* createHealthPowerup();
	static Ogre::Entity* createWallEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createTankEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createTankGunEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createGroundEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createProjectileEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createMissileEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createSoccerEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createBoxEntity(Ogre::SceneManager *sceneManager);
	static Ogre::Entity* createHealthPowerEntity(Ogre::SceneManager *sceneManager);
	static Ogre::ParticleSystem* createParticleSystem(Ogre::SceneManager *sceneManager, Ogre::String particleName);
	static Ogre::BillboardSet* createBillboardSet(Ogre::SceneManager* sceneManager);
	
private:
	static Ogre::String createUniqueObjectName(Ogre::String name);
	ObjectFactory();
	~ObjectFactory();
};

#endif