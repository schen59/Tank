#ifndef __PhysicsSoccer_h_
#define __PhysicsSoccer_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsSoccer : public PhysicsObject {
public:
	PhysicsSoccer(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsSoccer();
	Properties::ObjectType getType() const { return Properties::ObjectType::PROJECTILE; }

protected:
	void createCollisionShape();
};

#endif