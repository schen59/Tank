#ifndef __Shell_h_
#define __Shell_h_

#include "include\object\projectile\Projectile.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreShell;
class PhysicsShell;
class Projectile;

class Shell : public Projectile {
public:
	Shell(btScalar mass, btVector3 &size);
	~Shell();
	void explode(World *world);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();
};

#endif