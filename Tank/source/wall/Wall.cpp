#include "include\wall\Wall.h"
#include "include\wall\OgreWall.h"
#include "include\wall\PhysicsWall.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Wall::Wall(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Wall::~Wall() {
}

void Wall::addToWorld(World *world, btQuaternion &orientation, btVector3 &position) {
	mOgreWall = new OgreWall();
	mPhysicsWall = new PhysicsWall(orientation, position, mMass, mSize);
	mOgreWall->addToScene(world->getOgreWorld()->getSceneManager(), Ogre::Quaternion(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	world->getPhysicsWorld()->addObject(mPhysicsWall);
}