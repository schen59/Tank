#ifndef __Projectile_h_
#define __Projectile_h_

#include "include\object\AbstractObject.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreProjectile;
class PhysicsProjectile;
class AbstractObject;

class Projectile : public AbstractObject {
public:
	Projectile(btScalar mass, btVector3 &size);
	~Projectile();
	void setVelocity(btVector3 &velocity);
	bool isActive() const;
	void explode(World *world);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();

private:
	btScalar mMass;
	btVector3 mSize;
};

#endif