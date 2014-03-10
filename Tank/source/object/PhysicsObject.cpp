#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsObject::PhysicsObject(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

btQuaternion PhysicsObject::getOrientation() const {
	return mRigidBody->getWorldTransform().getRotation();
}

btVector3 PhysicsObject::getPosition() const {
	return mRigidBody->getWorldTransform().getOrigin();
}

void PhysicsObject::setOrientation(btQuaternion &orientation) {
	mRigidBody->getWorldTransform().setRotation(orientation);
}

void PhysicsObject::setPosition(btVector3 &position) {
	mRigidBody->getWorldTransform().setOrigin(position);
}

void PhysicsObject::createRigidBody(btQuaternion &orientation, btVector3 &position) {
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);
	bool isDynamic = (mMass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic) {
		mCollisionShape->calculateLocalInertia(mMass, localInertia);
	}
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, motionState, mCollisionShape, localInertia);
	mRigidBody = new btRigidBody(rbInfo);
}

PhysicsObject::~PhysicsObject() {
	if (mRigidBody && mRigidBody->getMotionState()) {
			delete mRigidBody->getMotionState();
			delete mRigidBody;
	}
	delete mCollisionShape;
}