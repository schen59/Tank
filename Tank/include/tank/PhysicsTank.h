#ifndef __PhysicsTank_h_
#define __PhysicsTank_h_

#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsTank : public PhysicsObject {
public:
	PhysicsTank(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsTank();

protected:
	void createCollisionShape();
};

#endif