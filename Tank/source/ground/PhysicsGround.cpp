#include "include\ground\PhysicsGround.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsGround::PhysicsGround(btQuaternion &orientation, btVector3 &position,
							 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsGround::~PhysicsGround() {
}

void PhysicsGround::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}