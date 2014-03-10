#include "include\core\PhysicsWorld.h"
#include "include\object\PhysicsObject.h"

#include <vector>
#include "btBulletDynamicsCommon.h"

PhysicsWorld::PhysicsWorld(btVector3 &gravity) {
	mGravity = gravity;
}

void PhysicsWorld::setup() {
	setupDynamicsWorld();
}

void PhysicsWorld::setupDynamicsWorld() {
    mDefaultCollisionConfiguration = new btDefaultCollisionConfiguration();
	mConstraintSolver = new btSequentialImpulseConstraintSolver;
	mCollisionDispatcher = new btCollisionDispatcher(mDefaultCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();
	mDynamicsWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, mBroadphaseInterface,
		mConstraintSolver, mDefaultCollisionConfiguration);
	mDynamicsWorld->setGravity(mGravity);
}

PhysicsWorld::~PhysicsWorld() {
	destroyObjects();
	delete mDynamicsWorld;
	delete mConstraintSolver;
	delete mBroadphaseInterface;
	delete mCollisionDispatcher;
	delete mDefaultCollisionConfiguration;
}

void PhysicsWorld::destroyObjects() {
	for (std::vector<PhysicsObject*>::iterator it=mObjects.begin(); it!=mObjects.end(); it++) {
		PhysicsObject *object = *it;
		delete object;
	}
	mObjects.clear();
}

void PhysicsWorld::addObject(PhysicsObject *object) {
	mDynamicsWorld->addRigidBody(object->getRigidBody());
	mObjects.push_back(object);
}

void PhysicsWorld::think(float time) {
	mDynamicsWorld->stepSimulation(time);
}