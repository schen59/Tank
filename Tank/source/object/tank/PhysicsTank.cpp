#include "include\object\PhysicsObject.h"
#include "include\object\tank\PhysicsTank.h"
#include "include\factory\ObjectFactory.h"

#include "btBulletDynamicsCommon.h"

PhysicsTank::PhysicsTank(btQuaternion &orientation, btVector3 &position, 
						 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsTank::~PhysicsTank() {
}

void PhysicsTank::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}