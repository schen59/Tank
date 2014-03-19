#include "include\object\wall\Wall.h"
#include "include\object\wall\OgreWall.h"
#include "include\object\wall\PhysicsWall.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Wall::Wall(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Wall::~Wall() {
}

void Wall::createOgreObject() {
	mOgreObject = new OgreWall();
}

void Wall::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsWall(orientation, position, mMass, mSize);
}