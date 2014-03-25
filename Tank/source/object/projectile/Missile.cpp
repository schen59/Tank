#include "include\object\projectile\Missile.h"
#include "include\object\projectile\OgreMissile.h"
#include "include\object\projectile\PhysicsMissile.h"
#include "include\object\projectile\Projectile.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Missile::Missile(btScalar mass, btVector3 &size) : Projectile(mass, size) {
}

Missile::~Missile() {
}

void Missile::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsMissile(orientation, position, mMass, mSize);
}

void Missile::createOgreObject() {
	mOgreObject = new OgreMissile();
}

void Missile::explode(World *world) {
	OgreMissile *ogreMissile = static_cast<OgreMissile*>(mOgreObject);
	ogreMissile->explode(world->getOgreWorld());
	mIsExploded = true;
}
