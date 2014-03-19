#ifndef __PhysicsBox_h_
#define __PhysicsBox_h_

#include "include\common\Properties.h"
#include "include\object\PhysicsObject.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject;

class PhysicsBox : public PhysicsObject {
public:
	PhysicsBox(btQuaternion &orientation, btVector3 &position, btScalar mass, btVector3 &size);
	~PhysicsBox();
	Properties::ObjectType getType() const { return Properties::ObjectType::OBSTACLE; }

protected:
	void createCollisionShape();
};

#endif