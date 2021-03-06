#ifndef __Missile_h_
#define __Missile_h_

#include "include\object\projectile\Projectile.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreMissile;
class PhysicsMissile;
class Projectile;

class Missile : public Projectile {
public:
	Missile(btScalar mass, btVector3 &size);
	~Missile();
	void explode(World *world);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();
};

#endif