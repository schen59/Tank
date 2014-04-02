#ifndef __Soccer_h_
#define __Soccer_h_

#include "include\object\projectile\Projectile.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreSoccer;
class PhysicsSoccer;
class Projectile;

class Soccer : public Projectile {
public:
	Soccer(btScalar mass, btVector3 &size);
	~Soccer();
	void explode(World *world);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();
};

#endif