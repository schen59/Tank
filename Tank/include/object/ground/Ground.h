#ifndef __Ground_h_
#define __Ground_h_

#include "include\object\AbstractObject.h"

#include "btBulletDynamicsCommon.h"

class World;
class OgreGround;
class PhysicsGround;
class AbstractObject;

class Ground : public AbstractObject {
public:
	Ground(btScalar mass, btVector3 &size);
	~Ground();
	void setFriction(float friction);

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();

private:
	btScalar mMass;
	btVector3 mSize;
};

#endif