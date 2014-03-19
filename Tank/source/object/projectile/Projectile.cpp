#include "include\object\projectile\Projectile.h"
#include "include\object\projectile\OgreProjectile.h"
#include "include\object\projectile\PhysicsProjectile.h"
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
}

Projectile::~Projectile() {
}

void Projectile::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsProjectile(orientation, position, mMass, mSize);
}

void Projectile::createOgreObject() {
	mOgreObject = new OgreProjectile();
}

void Projectile::setVelocity(btVector3 &velocity) {
	mPhysicsObject->getRigidBody()->activate();
	mPhysicsObject->getRigidBody()->setLinearVelocity(velocity);
}

bool Projectile::isActive() const {
	return mPhysicsObject->getRigidBody()->isActive();
}

void Projectile::explode(World *world) {
	OgreProjectile *ogreProjectile = static_cast<OgreProjectile*>(mOgreObject);
	ogreProjectile->explode(world->getOgreWorld());
}
