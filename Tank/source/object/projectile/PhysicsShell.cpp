#include "include\object\projectile\PhysicsShell.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsShell::PhysicsShell(btQuaternion &orientation, btVector3 &position, 
									 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsShell::~PhysicsShell() {
}

void PhysicsShell::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}