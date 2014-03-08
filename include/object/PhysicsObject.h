#ifndef __PhysicsObject_h_
#define __PhysicsObject_h_

#include "include\core\PhysicsWorld.h"

#include "btBulletDynamicsCommon.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"

namespace Ogre {
	class SceneNode;
	class Entity;
}

class PhysicsWorld;

class PhysicsObject {
public:
	PhysicsObject(btQuaternion &orientation, btVector3 &position, btScalar mass);
	void addToWorld(PhysicsWorld *physicsWorld);
	btRigidBody* getRigidBody() const { return mRigidBody; }
	Ogre::SceneNode* getSceneNode() { return mSceneNode; }
	~PhysicsObject();

protected:
	void setEntity(Ogre::Entity *entity) { mEntity = entity; }
	virtual void createCollisionShape() = 0;

	btCollisionShape *mCollisionShape;

private:
	void addToScene(Ogre::SceneManager *sceneManager);
	virtual void load(Ogre::SceneManager *sceneManager) = 0;
	void createRigidBody();

	btScalar mMass;
	btQuaternion mOrientation;
	btVector3 mPosition;
	btRigidBody *mRigidBody;

	Ogre::SceneNode *mSceneNode;
	Ogre::Entity *mEntity;
};

#endif