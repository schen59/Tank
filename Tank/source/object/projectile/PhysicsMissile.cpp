#include "include\object\projectile\PhysicsMissile.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsMissile::PhysicsMissile(btQuaternion &orientation, btVector3 &position, 
									 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsMissile::~PhysicsMissile() {
}

void PhysicsMissile::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}