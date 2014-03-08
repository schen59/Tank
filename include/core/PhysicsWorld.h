#ifndef __PhysicsWorld_h_
#define __PhysicsWorld_h_

#include "include\handler\InputHandler.h"
#include "include\object\AbstractObject.h"
#include "include\object\PhysicsObject.h"

#include "btBulletDynamicsCommon.h"
#include <vector>

class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btConstraintSolver;
class btCollisionDispatcher;
class btBroadphaseInterface;
class PhysicsObject;

namespace Ogre {
	class SceneManager;
}

class InputHandler;

class PhysicsWorld {
public:
	PhysicsWorld(Ogre::SceneManager *sceneManager, InputHandler *inputHandler);
	~PhysicsWorld();
	void addObject(PhysicsObject *object);
	Ogre::SceneManager* getSceneManager() { return mSceneManager; }
	void setup();

private:
	void destroyObjects();
	void setupDynamicsWorld();

	btDynamicsWorld *mDynamicsWorld;
	btDefaultCollisionConfiguration *mDefaultCollisionConfiguration;
	btConstraintSolver *mConstraintSolver;
	btCollisionDispatcher *mCollisionDispatcher;
	btBroadphaseInterface *mBroadphaseInterface;
	Ogre::SceneManager *mSceneManager;
	InputHandler *mInputHandler;
	std::vector<PhysicsObject*> mObjects;
};

#endif