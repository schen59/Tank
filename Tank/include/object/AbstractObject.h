#ifndef __AbstractObject_h_
#define __AbstractObject_h_

#include "btBulletDynamicsCommon.h"

class World;
class PhysicsObject;
class OgreObject;

class AbstractObject {
public:
	AbstractObject();
	~AbstractObject();
	void addToWorld(World *world, btQuaternion &orientation, btVector3 &position);
	PhysicsObject* getPhysicsObject() const { return mPhysicsObject; }
	OgreObject* getOgreObject() const { return mOgreObject; }
	void update();
	bool isCollidedWith(AbstractObject *object) const;
	bool isCollided() const;

protected:
	virtual void createPhysicsObject(btQuaternion &orientation, btVector3 &position) = 0;
	virtual void createOgreObject() = 0;

	PhysicsObject *mPhysicsObject;
	OgreObject *mOgreObject;
};

#endif