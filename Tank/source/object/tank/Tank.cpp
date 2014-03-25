#include "include\object\tank\Tank.h"
#include "include\object\tank\OgreTank.h"
#include "include\object\tank\PhysicsTank.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\projectile\Shell.h"
#include "include\object\projectile\Missile.h"
#include "include\factory\ObjectFactory.h"
#include "include\object\AbstractObject.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"
#include "btBulletDynamicsCommon.h"

Tank::Tank(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
	mIsAlive = true;
	mTimer.reset();
}

void Tank::move(float time) {
	Ogre::Vector3 direction = mOgreObject->getDirection();
	direction.normalise();
	//btVector3 direction = mPhysicsObject->getDirection();
	//direction = direction.normalize();
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * (time > 0 ? mMass*10 : -mMass*10);
	mPhysicsObject->getRigidBody()->activate();
	mPhysicsObject->getRigidBody()->applyCentralForce(velocity);
}

void Tank::yaw(float degree) {
	mPhysicsObject->getRigidBody()->activate();
	//mPhysicsObject->setOrientation(btQuaternion(0, sin(degree), 0, cos(degree)));
	mPhysicsObject->getRigidBody()->setAngularVelocity(btVector3(0, degree>0 ? 0.5 : -0.5, 0));
}

void Tank::createOgreObject() {
	mOgreObject = new OgreTank();
}

void Tank::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsTank(orientation, position, mMass, mSize);
}

bool Tank::isShellEnabled() {
	return mTimer.getMilliseconds() > 2000;
}

bool Tank::isMissileEnabled() {
	return mTimer.getMilliseconds() > 200;
}

Shell* Tank::fireShell(World *world) {
	//if (mTimer.getMilliseconds() > 2000) {
	//	mEnabled = true;
	//}
	Shell *shell = ObjectFactory::createShell(0.5, btVector3(1, 1, 1));
	btVector3 position = mPhysicsObject->getPosition();
	Ogre::Vector3 direction = mOgreObject->getOrientation() * Ogre::Vector3(0, 0.05, -1);
	//Ogre::Vector3 direction = mOgreObject->getDirection();
	direction.normalise();
	shell->addToWorld(world, btQuaternion(0, 0, 0, 1), position + btVector3(direction.x*3, direction.y*3, direction.z*3));
	//projectile->addToWorld(world, btQuaternion(0, 0, 0, 1), btVector3(0, 10, -10));
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * 100;
	//btVector3 velocity = btVector3(1, 1, 0) * 20;
	shell->setVelocity(velocity);
	mTimer.reset();
	return shell;
}

Missile* Tank::fireMissile(World *world) {
	Missile *missile = ObjectFactory::createMissile(0.5, btVector3(1, 1, 1));
	btVector3 position = mPhysicsObject->getPosition();
	Ogre::Vector3 direction = mOgreObject->getOrientation() * Ogre::Vector3(0, 0.05, -1);
	direction.normalise();
	missile->addToWorld(world, btQuaternion(0, 0, 0, 1), position + btVector3(direction.x*3, direction.y*3, direction.z*3));
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * 100;
	missile->setVelocity(velocity);
	mTimer.reset();
	return missile;
}

void Tank::reset() {
	mPhysicsObject->setOrientation(btQuaternion(0, 0, 0, 1));
	update();
}

Tank::~Tank() {
}

void Tank::attacked() {
	mIsAlive = false;
}

bool Tank::isAlive() const {
	return mIsAlive;
}

void Tank::explode(World *world) {
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	ogreTank->explode(world->getOgreWorld());
}