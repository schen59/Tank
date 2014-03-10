#include "include\ground\Ground.h"
#include "include\ground\OgreGround.h"
#include "include\ground\PhysicsGround.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Ground::Ground(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Ground::~Ground() {
}

void Ground::addToWorld(World *world, btQuaternion &orientation, btVector3 &position) {
	mOgreGround = new OgreGround();
	mPhysicsGround = new PhysicsGround(orientation, position, mMass, mSize);
	mOgreGround->addToScene(world->getOgreWorld()->getSceneManager(), Ogre::Quaternion(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	world->getPhysicsWorld()->addObject(mPhysicsGround);
}

void Ground::setFriction(float friction) {
	mPhysicsGround->getRigidBody()->setFriction(friction);
}