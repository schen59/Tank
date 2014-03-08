#include "include\core\PhysicsWorld.h"
#include "include\object\PhysicsGround.h"

#include <vector>
#include "btBulletDynamicsCommon.h"

PhysicsWorld::PhysicsWorld(Ogre::SceneManager *sceneManager, InputHandler *inputHandler) {
	mSceneManager = sceneManager;
	mInputHandler = inputHandler;
}

void PhysicsWorld::setup() {
	setupDynamicsWorld();
	PhysicsGround *ground = new PhysicsGround(btQuaternion(0, 0, 0, 1), btVector3(0, -10, 0), btScalar(0.));
	ground->addToWorld(this);
}

void PhysicsWorld::setupDynamicsWorld() {
    mDefaultCollisionConfiguration = new btDefaultCollisionConfiguration();
	mConstraintSolver = new btSequentialImpulseConstraintSolver;
	mCollisionDispatcher = new btCollisionDispatcher(mDefaultCollisionConfiguration);
	mBroadphaseInterface = new btDbvtBroadphase();
	mDynamicsWorld = new btDiscreteDynamicsWorld(mCollisionDispatcher, mBroadphaseInterface,
		mConstraintSolver, mDefaultCollisionConfiguration);
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