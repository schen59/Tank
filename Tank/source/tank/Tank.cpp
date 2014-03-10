#include "include\tank\Tank.h"
#include "include\tank\OgreTank.h"
#include "include\tank\PhysicsTank.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\projectile\Projectile.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"
#include "btBulletDynamicsCommon.h"

Tank::Tank(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

void Tank::move(float time) {
	Ogre::Vector3 direction = mOgreTank->getDirection();
	direction.normalise();
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * (time > 0 ? 5 : -5);
	mPhysicsTank->getRigidBody()->activate();
	mPhysicsTank->getRigidBody()->applyCentralForce(velocity);
}

void Tank::yaw(float degree) {
	mPhysicsTank->getRigidBody()->activate();
	mPhysicsTank->getRigidBody()->setAngularVelocity(btVector3(0, degree>0 ? 0.2 : -0.2, 0));
}

void Tank::addToWorld(World *world, btQuaternion &orientation, btVector3 &position) {
	mOgreTank = new OgreTank();
	mPhysicsTank = new PhysicsTank(orientation, position, mMass, mSize);
	mOgreTank->addToScene(world->getOgreWorld()->getSceneManager(), Ogre::Quaternion(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	world->getPhysicsWorld()->addObject(mPhysicsTank);

}

void Tank::update() {
	btQuaternion orientation = mPhysicsTank->getOrientation();
	btVector3 position = mPhysicsTank->getPosition();
	mOgreTank->setOrientation(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ());
	mOgreTank->setPosition(Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
}

Projectile* Tank::fire(World *world) {
	Projectile *projectile = ObjectFactory::createProjectile(0.5, btVector3(0.5, 0.5, 0.5));
	btVector3 position = mPhysicsTank->getPosition();
	Ogre::Vector3 direction = mOgreTank->getOrientation() * Ogre::Vector3(0, 1, -1);
	direction.normalise();
	projectile->addToWorld(world, btQuaternion(0, 0, 0, 1), position + btVector3(direction.x, direction.y, direction.z));
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * 20;
	projectile->setVelocity(velocity);
	return projectile;
}

btVector3 Tank::getPosition() const {
	return mPhysicsTank->getPosition(); 
}

void Tank::reset() {
	mPhysicsTank->setOrientation(btQuaternion(0, 0, 0, 1));
	update();
}

Tank::~Tank() {
	delete mOgreTank;
	delete mPhysicsTank;
}