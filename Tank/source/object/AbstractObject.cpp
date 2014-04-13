#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\core\World.h"

#include "Ogre.h"
#include "btBulletDynamicsCommon.h"

AbstractObject::AbstractObject() {
}

AbstractObject::~AbstractObject() {
}

void AbstractObject::addToWorld(World *world, btQuaternion &orientation, btVector3 &position) {
	createOgreObject();
	createPhysicsObject(orientation, position);
	world->getOgreWorld()->addObject(mOgreObject, Ogre::Quaternion(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	//mOgreObject->addToScene(world->getOgreWorld()->getSceneManager(), Ogre::Quaternion(orientation.getW(), orientation.getX(),
	//	orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	world->getPhysicsWorld()->addObject(mPhysicsObject);
}

void AbstractObject::addToWorld(World *world, Ogre::Quaternion &orientation, Ogre::Vector3 &position) {
	addToWorld(world, btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w),
		btVector3(position.x, position.y, position.z));
}

void AbstractObject::update() {
	btQuaternion orientation = mPhysicsObject->getOrientation();
	btVector3 position = mPhysicsObject->getPosition();
	mOgreObject->setOrientation(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ());
	mOgreObject->setPosition(Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
}

bool AbstractObject::isCollidedWith(AbstractObject *object) const {
	return mPhysicsObject->isCollidedWith(object->getPhysicsObject());
}

bool AbstractObject::isCollided() const {
	return mPhysicsObject->isCollided();
}