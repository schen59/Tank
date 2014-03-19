#ifndef __PhysicsObject_h_
#define __PhysicsObject_h_

#include "include\common\Properties.h"
#include "btBulletDynamicsCommon.h"

class PhysicsObject {
public:
	PhysicsObject(btScalar mass, btVector3 &size);
	btRigidBody* getRigidBody() const { return mRigidBody; }
	btQuaternion getOrientation() const;
	btVector3 getDirection() const;
	void setOrientation(btQuaternion &orientation);
	btVector3 getPosition() const;
	void setPosition(btVector3 &position);
	btVector3 getSize() const { return mSize; }
	btScalar getMass() const { return mMass; }
	~PhysicsObject();
	void setIsCollided(bool isCollided);
	bool isCollided() const;
	bool isCollidedWith(PhysicsObject *object) const;
	virtual Properties::ObjectType getType() const = 0;

protected:
	virtual void createCollisionShape() = 0;
	void createRigidBody(btQuaternion &orientation, btVector3 &position);

	btCollisionShape *mCollisionShape;

private:
	bool mIsCollided;
	btScalar mMass;
	btVector3 mSize;
	btRigidBody *mRigidBody;
};

#endif