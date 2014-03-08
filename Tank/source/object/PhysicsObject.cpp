#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

PhysicsObject::PhysicsObject(btQuaternion &orientation, btVector3 &position, btScalar mass) {
	mOrientation = orientation;
	mPosition = position;
	mMass = mass;
}

void PhysicsObject::addToWorld(PhysicsWorld *physicsWorld) {
	load(physicsWorld->getSceneManager());
	addToScene(physicsWorld->getSceneManager());
	createCollisionShape();
	createRigidBody();
	physicsWorld->addObject(this);
}

void PhysicsObject::createRigidBody() {
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(mPosition);
	bool isDynamic = (mMass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic) {
		mCollisionShape->calculateLocalInertia(mMass, localInertia);
	}
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, motionState, mCollisionShape, localInertia);
	mRigidBody = new btRigidBody(rbInfo);
}

void PhysicsObject::addToScene(Ogre::SceneManager *sceneManager) {
	mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mEntity);
	mSceneNode->setPosition(mPosition.getX(), mPosition.getY(), mPosition.getZ());
	mSceneNode->setOrientation(Ogre::Quaternion(mOrientation.getW(), mOrientation.getX(), mOrientation.getY(),
		mOrientation.getZ()));
}

PhysicsObject::~PhysicsObject() {
	if (mRigidBody && mRigidBody->getMotionState()) {
			delete mRigidBody->getMotionState();
			delete mRigidBody;
	}
}