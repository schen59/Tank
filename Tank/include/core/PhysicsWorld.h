#ifndef __PhysicsWorld_h_
#define __PhysicsWorld_h_

#include <vector>
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsWorld {
public:
	PhysicsWorld(btVector3 &gravity);
	~PhysicsWorld();
	void addObject(PhysicsObject *object);

	void setup();

	void think(float time);

private:
	void destroyObjects();
	void setupDynamicsWorld();

	btVector3 mGravity;
	btDynamicsWorld *mDynamicsWorld;
	btDefaultCollisionConfiguration *mDefaultCollisionConfiguration;
	btConstraintSolver *mConstraintSolver;
	btCollisionDispatcher *mCollisionDispatcher;
	btBroadphaseInterface *mBroadphaseInterface;
	std::vector<PhysicsObject*> mObjects;
};

#endif