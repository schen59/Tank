#include "include\object\projectile\PhysicsSoccer.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsSoccer::PhysicsSoccer(btQuaternion &orientation, btVector3 &position, 
									 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsSoccer::~PhysicsSoccer() {
}

void PhysicsSoccer::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}