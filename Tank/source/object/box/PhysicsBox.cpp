#include "include\object\box\PhysicsBox.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsBox::PhysicsBox(btQuaternion &orientation, btVector3 &position,
							 btScalar mass, btVector3 &size) : PhysicsObject(mass, size) {
	createCollisionShape();
	createRigidBody(orientation, position);
}

PhysicsBox::~PhysicsBox() {
}

void PhysicsBox::createCollisionShape() {
	btVector3 halfSize = getSize() / 2;
	mCollisionShape = new btBoxShape(halfSize);
}