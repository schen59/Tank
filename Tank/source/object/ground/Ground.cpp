#include "include\object\ground\Ground.h"
#include "include\object\ground\OgreGround.h"
#include "include\object\ground\PhysicsGround.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Ground::Ground(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Ground::~Ground() {
}

void Ground::createOgreObject() {
	mOgreObject = new OgreGround();
}

void Ground::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsGround(orientation, position, mMass, mSize);
}

void Ground::setFriction(float friction) {
	mPhysicsObject->getRigidBody()->setFriction(friction);
}