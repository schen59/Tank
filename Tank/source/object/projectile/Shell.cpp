#include "include\object\projectile\Shell.h"
#include "include\object\projectile\OgreShell.h"
#include "include\object\projectile\PhysicsShell.h"
#include "include\object\projectile\Projectile.h"
#include "include\core\World.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\object\AbstractObject.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Shell::Shell(btScalar mass, btVector3 &size) : Projectile(mass, size) {
}

Shell::~Shell() {
}

void Shell::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsShell(orientation, position, mMass, mSize);
}

void Shell::createOgreObject() {
	mOgreObject = new OgreShell();
}

void Shell::explode(World *world) {
	OgreShell *ogreShell = static_cast<OgreShell*>(mOgreObject);
	ogreShell->explode(world->getOgreWorld());
	mIsExploded = true;
}
