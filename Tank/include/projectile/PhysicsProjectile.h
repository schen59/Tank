#ifndef __PhysicsProjectile_h_
#define __PhysicsProjectile_h_

#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsProjectile : public PhysicsObject {
public:
	PhysicsProjectile(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsProjectile();

protected:
	void createCollisionShape();
};

#endif