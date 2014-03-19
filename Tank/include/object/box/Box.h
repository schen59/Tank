#ifndef __Box_h_
#define __Box_h_

#include "include\object\AbstractObject.h"
#include "btBulletDynamicsCommon.h"

class AbstractObject;

class Box : public AbstractObject {
public:
	Box(btScalar mass, btVector3 &size);
	~Box();

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();

private:
	btScalar mMass;
	btVector3 mSize;
};

#endif