#ifndef __PhysicsGround_h_
#define __PhysicsGround_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsGround : public PhysicsObject {
public:
	PhysicsGround(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsGround();
	Properties::ObjectType getType() const { return Properties::ObjectType::GROUND; }

protected:
	void createCollisionShape();
};

#endif