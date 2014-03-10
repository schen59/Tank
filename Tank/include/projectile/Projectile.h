#ifndef __Projectile_h_
#define __Projectile_h_

#include "btBulletDynamicsCommon.h"

class World;
class OgreProjectile;
class PhysicsProjectile;

class Projectile {
public:
	Projectile(btScalar mass, btVector3 &size);
	~Projectile();
	void addToWorld(World *world, btQuaternion &orientation, btVector3 &position);
	void setVelocity(btVector3 &velocity);
	void update();

private:
	OgreProjectile *mOgreProjectile;
	PhysicsProjectile *mPhysicsProjectile;
	btScalar mMass;
	btVector3 mSize;
};

#endif