#ifndef __Projectile_h_
#define __Projectile_h_

#include "include\object\AbstractObject.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreShell;
class PhysicsShell;
class AbstractObject;

class Projectile : public AbstractObject {
public:
	Projectile(btScalar mass, btVector3 &size);
	~Projectile();
	void setVelocity(btVector3 &velocity);
	bool isActive() const;
	virtual void explode(World *world) = 0;
	bool isExploded() const { return mIsExploded; }

protected:
	bool mIsExploded;
	btScalar mMass;
	btVector3 mSize;
};

#endif
