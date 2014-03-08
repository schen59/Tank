#ifndef __PhysicsGround_h_
#define __PhysicsGround_h_

#include "include\object\PhysicsObject.h"

#include "OgreSceneManager.h"
#include "btBulletDynamicsCommon.h"

namespace Ogre {
	class SceneManager;
}

class PhysicsObject;

class PhysicsGround : public PhysicsObject {
public:
	PhysicsGround(btQuaternion &orientation, btVector3 &position, btScalar mass);
	~PhysicsGround();
	void load(Ogre::SceneManager *sceneManager);

protected:
	void createCollisionShape();
};

#endif