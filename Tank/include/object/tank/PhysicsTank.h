#ifndef __PhysicsTank_h_
#define __PhysicsTank_h_

#include "include\object\AbstractObject.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsTank : public PhysicsObject {
public:
	PhysicsTank(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsTank();
	Properties::ObjectType getType() const { return Properties::ObjectType::TANK; }

protected:
	void createCollisionShape();
};

#endif