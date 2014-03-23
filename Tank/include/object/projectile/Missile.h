#ifndef __Missile_h_
#define __Missile_h_

#include "include\object\AbstractObject.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreMissile;
class PhysicsMissile;
class AbstractObject;

class Missile : public AbstractObject {
public:
	Missile(btScalar mass, btVector3 &size);
	~Missile();
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