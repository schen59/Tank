#include "include\projectile\Projectile.h"
#include "include\projectile\OgreProjectile.h"
#include "include\projectile\PhysicsProjectile.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Projectile::Projectile(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Projectile::~Projectile() {
	delete mOgreProjectile;
	delete mPhysicsProjectile;
}

void Projectile::addToWorld(World *world, btQuaternion &orientation, btVector3 &position) {
	mOgreProjectile = new OgreProjectile();
	mPhysicsProjectile = new PhysicsProjectile(orientation, position, mMass, mSize);
	mOgreProjectile->addToScene(world->getOgreWorld()->getSceneManager(), Ogre::Quaternion(orientation.getW(), orientation.getX(),
		orientation.getY(), orientation.getZ()), Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
	world->getPhysicsWorld()->addObject(mPhysicsProjectile);
}

void Projectile::setVelocity(btVector3 &velocity) {
	mPhysicsProjectile->getRigidBody()->activate();
	mPhysicsProjectile->getRigidBody()->setLinearVelocity(velocity);
}

void Projectile::update() {
	btQuaternion orientation = mPhysicsProjectile->getOrientation();
	btVector3 position = mPhysicsProjectile->getPosition();
	mOgreProjectile->setOrientation(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ());
	mOgreProjectile->setPosition(Ogre::Vector3(position.getX(), position.getY(), position.getZ()));
}