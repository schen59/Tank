#include "include\object\tank\Tank.h"
#include "include\object\tank\OgreTank.h"
#include "include\object\tank\PhysicsTank.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\projectile\Shell.h"
#include "include\object\projectile\Missile.h"
#include "include\object\projectile\Soccer.h"
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
	mHealth = 3.0;
	mTimer.reset();
}

void Tank::move(float time) {
	Ogre::Vector3 direction = mOgreObject->getDirection();
	direction.normalise();
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * (time > 0 ? mMass*10 : -mMass*10);
	mPhysicsObject->getRigidBody()->activate();
	mPhysicsObject->getRigidBody()->applyCentralForce(velocity);
}

void Tank::yaw(float degree) {
	mPhysicsObject->getRigidBody()->activate();
	mPhysicsObject->getRigidBody()->setAngularVelocity(btVector3(0, degree>0 ? 0.5 : -0.5, 0));
}

void Tank::yawBarrel(float degree) {
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	ogreTank->yawBarrel(degree);
}

void Tank::pitchBarrel(float degree) {
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	ogreTank->pitchBarrel(degree);
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
	return mTimer.getMilliseconds() > 1000;
}

bool Tank::isSoccerEnabled() {
	return mTimer.getMilliseconds() > 200;
}

Shell* Tank::fireShell(World *world) {
	Shell *shell = ObjectFactory::createShell(0.5, btVector3(1, 1, 1));
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	Ogre::Vector3 tankPosition = ogreTank->getPosition();
	Ogre::Vector3 barrelWorldPosition = ogreTank->getBarrelWorldPosition();
	shell->addToWorld(world, Ogre::Quaternion(1, 0, 0, 0), tankPosition + barrelWorldPosition);
	barrelWorldPosition.normalise();
	btVector3 velocity = btVector3(barrelWorldPosition.x, barrelWorldPosition.y, barrelWorldPosition.z) * 100;
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

Soccer* Tank::fireSoccer(World *world) {
	Soccer *soccer = ObjectFactory::createSoccer(0.5, btVector3(1, 1, 1));
	btVector3 position = mPhysicsObject->getPosition();
	Ogre::Vector3 direction = mOgreObject->getOrientation() * Ogre::Vector3(0, 0.05, -1);
	direction.normalise();
	soccer->addToWorld(world, btQuaternion(0, 0, 0, 1), position + btVector3(direction.x*3, direction.y*3, direction.z*3));
	btVector3 velocity = btVector3(direction.x, direction.y, direction.z) * 100;
	soccer->setVelocity(velocity);
	mTimer.reset();
	return soccer;
}
void Tank::reset() {
	mPhysicsObject->setOrientation(btQuaternion(0, 0, 0, 1));
	update();
}

Tank::~Tank() {
}

void Tank::attacked() {
	updateHealth(mHealth - 0.25);
}

void Tank::updateHealth(float health) {
	mHealth = health;
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	ogreTank->updateHealthBar(mHealth);
	if (mHealth == 0) {
		mIsAlive = false;
	}
}

void Tank::increaseHealth() {
	if (mHealth <= 3.0) {
	    updateHealth(mHealth + 0.25);
	}
}

bool Tank::isAlive() const {
	return mIsAlive;
}

void Tank::explode(World *world) {
	OgreTank *ogreTank = static_cast<OgreTank*>(mOgreObject);
	ogreTank->explode(world->getOgreWorld());
}