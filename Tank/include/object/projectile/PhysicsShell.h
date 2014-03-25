#ifndef __PhysicsShell_h_
#define __PhysicsShell_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsShell : public PhysicsObject {
public:
	PhysicsShell(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsShell();
	Properties::ObjectType getType() const { return Properties::ObjectType::PROJECTILE; }

protected:
	void createCollisionShape();
};

#endif