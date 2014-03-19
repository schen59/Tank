#ifndef __Wall_h_
#define __Wall_h_

#include "include\object\AbstractObject.h"
#include "btBulletDynamicsCommon.h"

class World;
class OgreWall;
class PhysicsWall;
class AbstractObject;

class Wall : public AbstractObject {
public:
	Wall(btScalar mass, btVector3 &size);
	~Wall();

protected:
	void createPhysicsObject(btQuaternion &orientation, btVector3 &position);
	void createOgreObject();

private:
	btScalar mMass;
	btVector3 mSize;
};

#endif