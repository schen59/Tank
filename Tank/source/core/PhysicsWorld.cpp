#include "include\core\PhysicsWorld.h"
#include "include\object\PhysicsObject.h"
#include "include\common\Properties.h"

#include <set>
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

void PhysicsWorld::desctroyDynamicsWorld() {
	for (int i=mDynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		mDynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
}

PhysicsWorld::~PhysicsWorld() {
	destroyObjects();
	desctroyDynamicsWorld();
	delete mDynamicsWorld;
	delete mConstraintSolver;
	delete mBroadphaseInterface;
	delete mCollisionDispatcher;
	delete mDefaultCollisionConfiguration;
}

void PhysicsWorld::destroyObjects() {
	std::set<PhysicsObject*>::iterator it=mObjects.begin();
	while (it != mObjects.end()) {
		PhysicsObject *object = *it;
		it++;
		removeObject(object);
		delete object;
	}
	mObjects.clear();
}

void PhysicsWorld::removeObject(PhysicsObject *object) {
	btRigidBody *rigidBody = object->getRigidBody();
	btCollisionShape *collisionShape = rigidBody->getCollisionShape();
	if (rigidBody && rigidBody->getMotionState()) {
		delete rigidBody->getMotionState();
		mDynamicsWorld->removeRigidBody(rigidBody);
	    delete collisionShape;
	}
	mObjects.erase(mObjects.find(object));
}

void PhysicsWorld::addObject(PhysicsObject *object) {
	mDynamicsWorld->addRigidBody(object->getRigidBody());
	mObjects.insert(object);
}

void PhysicsWorld::think(float time) {
	mDynamicsWorld->stepSimulation(time);
	detectCollision();
}

void PhysicsWorld::detectCollision() {
	int numManifolds = mDynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  mDynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
		PhysicsObject *objectA = static_cast<PhysicsObject*>(obA->getUserPointer());
		PhysicsObject *objectB = static_cast<PhysicsObject*>(obB->getUserPointer());
		objectA->setIsCollided(false);
		objectB->setIsCollided(false);
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f && ((objectA->getType()==Properties::PROJECTILE || objectB->getType()==Properties::PROJECTILE) || (objectA->getType()==Properties::MISSILE || objectB->getType()==Properties::MISSILE)) &&
				!(objectA->isCollided() && objectB->isCollided()))
			{
				objectA->setIsCollided(true);
				objectB->setIsCollided(true);
			}
		}
	}
}