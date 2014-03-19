#include "include\object\box\Box.h"
#include "include\object\box\OgreBox.h"
#include "include\object\box\PhysicsBox.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneManager.h"

Box::Box(btScalar mass, btVector3 &size) {
	mMass = mass;
	mSize = size;
}

Box::~Box() {
}

void Box::createOgreObject() {
	mOgreObject = new OgreBox();
}

void Box::createPhysicsObject(btQuaternion &orientation, btVector3 &position) {
	mPhysicsObject = new PhysicsBox(orientation, position, mMass, mSize);
}
