#include "include\projectile\PhysicsProjectile.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsProjectile::PhysicsProjectile(btQuaternion &orientation, btVector3 &position, 
									 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsProjectile::~PhysicsProjectile() {
}

void PhysicsProjectile::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}