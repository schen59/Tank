#ifndef __PhysicsMissile_h_
#define __PhysicsMissile_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsMissile : public PhysicsObject {
public:
	PhysicsMissile(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsMissile();
	Properties::ObjectType getType() const { return Properties::ObjectType::PROJECTILE; }

protected:
	void createCollisionShape();
};

#endif