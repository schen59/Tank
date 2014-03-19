#include "include\object\wall\PhysicsWall.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsWall::PhysicsWall(btQuaternion &orientation, btVector3 &position, 
						 btScalar mass, btVector3 &size) :  PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsWall::~PhysicsWall() {
}

void PhysicsWall::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}