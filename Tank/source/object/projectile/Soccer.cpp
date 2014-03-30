#include "include\object\projectile\Soccer.h"
#include "include\object\projectile\OgreSoccer.h"
#include "include\object\projectile\PhysicsSoccer.h"
#include "include\object\projectile\Projectile.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Soccer::Soccer(btScalar mass, btVector3 &size) : Projectile(mass, size) {
}

Soccer::~Soccer() {
}

void Soccer::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsSoccer(orientation, position, mMass, mSize);
}

void Soccer::createOgreObject() {
	mOgreObject = new OgreSoccer();
}

void Soccer::explode(World *world) {
	OgreSoccer *ogreSoccer = static_cast<OgreSoccer*>(mOgreObject);
	ogreSoccer->explode(world->getOgreWorld());
	mIsExploded = true;
}
