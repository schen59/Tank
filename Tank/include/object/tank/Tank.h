#ifndef __Tank_h_
#define __Tank_h_

#include "include\common\Properties.h"
#include "include\object\AbstractObject.h"
#include "btBulletDynamicsCommon.h"
#include "Ogre.h"

class OgreTank;
class PhysicsTank;
class World;
class Shell;
class Missile;
class AbstractObject;

class Tank : public AbstractObject {
public:
	Tank(btScalar mass, btVector3 &size);
	~Tank();
	void move(float time);
	void yaw(float degree);
	Shell* fireShell(World *world);
	Missile* fireMissile(World *world);
	bool isShellEnabled();
	bool isMissileEnabled();
	void reset();
	bool isAlive() const;
	void attacked();
	void explode(World *world);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();

private:
	btScalar mMass;
	btVector3 mSize;
	Ogre::Timer mTimer;
	bool mIsAlive;
};

#endif