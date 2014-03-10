#ifndef __Ground_h_
#define __Ground_h_

#include "btBulletDynamicsCommon.h"

class World;
class OgreGround;
class PhysicsGround;

class Ground {
public:
	Ground(btScalar mass, btVector3 &size);
	~Ground();
	void addToWorld(World *world, btQuaternion &orientation, btVector3 &position);
	void setFriction(float friction);

private:
	OgreGround *mOgreGround;
	PhysicsGround *mPhysicsGround;
	btScalar mMass;
	btVector3 mSize;
};

#endif