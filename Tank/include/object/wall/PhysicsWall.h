#ifndef __PhysicsWall_h_
#define __PhysicsWall_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsWall : public PhysicsObject {
public:
	PhysicsWall(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsWall();
	Properties::ObjectType getType() const { return Properties::ObjectType::WALL; }

protected:
	void createCollisionShape();
};

#endif