#ifndef __PhysicsGround_h_
#define __PhysicsGround_h_

#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsGround : public PhysicsObject {
public:
	PhysicsGround(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsGround();

protected:
	void createCollisionShape();
};

#endif