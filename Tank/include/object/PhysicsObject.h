#ifndef __PhysicsObject_h_
#define __PhysicsObject_h_

#include "btBulletDynamicsCommon.h"

class PhysicsObject {
public:
	PhysicsObject(btScalar mass, btVector3 &size);
	btRigidBody* getRigidBody() const { return mRigidBody; }
	btQuaternion getOrientation() const;
	void setOrientation(btQuaternion &orientation);
	btVector3 getPosition() const;
	void setPosition(btVector3 &position);
	btVector3 getSize() const { return mSize; }
	btScalar getMass() const { return mMass; }
	~PhysicsObject();

protected:
	virtual void createCollisionShape() = 0;
	void createRigidBody(btQuaternion &orientation, btVector3 &position);

	btCollisionShape *mCollisionShape;

private:
	
	btScalar mMass;
	btVector3 mSize;
	btRigidBody *mRigidBody;
};

#endif