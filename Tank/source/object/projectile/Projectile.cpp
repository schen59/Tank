#include "include\object\projectile\Projectile.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Projectile::Projectile(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
	mIsExploded = false;
}

Projectile::~Projectile() {
}

void Projectile::setVelocity(btVector3 &velocity) {
	mPhysicsObject->getRigidBody()->activate();
	mPhysicsObject->getRigidBody()->setLinearVelocity(velocity);
}

bool Projectile::isActive() const {
	return mPhysicsObject->getRigidBody()->isActive();
}

