#include "include\object\PhysicsGround.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "btBulletDynamicsCommon.h"

PhysicsGround::PhysicsGround(btQuaternion &orientation, btVector3 &position, btScalar mass) : PhysicsObject(orientation, position, mass) {
}

PhysicsGround::~PhysicsGround() {
}

void PhysicsGround::load(Ogre::SceneManager *sceneManager) {
	Ogre::Entity *entity = ObjectFactory::createGroundEntity(sceneManager);
	setEntity(entity);
}

void PhysicsGround::createCollisionShape() {
	mCollisionShape = new btBoxShape(btVector3(btScalar(10.),btScalar(10.),btScalar(10.)));
}