#ifndef __Tank_h_
#define __Tank_h_

#include "btBulletDynamicsCommon.h"

class OgreTank;
class PhysicsTank;
class World;
class Projectile;

class Tank {
public:
	Tank(btScalar mass, btVector3 &size);
	~Tank();
	void move(float time);
	void yaw(float degree);
	void update();
	void addToWorld(World *world, btQuaternion &orientation, btVector3 &position);
	OgreTank* getOgreTank() const { return mOgreTank; }
	btVector3 getPosition() const;
	Projectile* fire(World *world);
	void reset();

private:
	OgreTank *mOgreTank;
	PhysicsTank *mPhysicsTank;
	btScalar mMass;
	btVector3 mSize;
};

#endif