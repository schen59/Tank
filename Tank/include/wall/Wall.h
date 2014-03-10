#ifndef __Wall_h_
#define __Wall_h_

#include "btBulletDynamicsCommon.h"

class World;
class OgreWall;
class PhysicsWall;

class Wall {
public:
	Wall(btScalar mass, btVector3 &size);
	~Wall();
	void addToWorld(World *world, btQuaternion &orientation, btVector3 &position);

private:
	OgreWall *mOgreWall;
	PhysicsWall *mPhysicsWall;
	btScalar mMass;
	btVector3 mSize;
};

#endif