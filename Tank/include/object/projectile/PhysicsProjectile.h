#ifndef __PhysicsProjectile_h_
#define __PhysicsProjectile_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsProjectile : public PhysicsObject {
public:
	PhysicsProjectile(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsProjectile();
	Properties::ObjectType getType() const { return Properties::ObjectType::PROJECTILE; }

protected:
	void createCollisionShape();
};

#endif