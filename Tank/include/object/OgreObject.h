#ifndef __OgreObject_h_
#define __OgreObject_h_

#include "Ogre.h"

namespace Ogre {
	class SceneNode;
	class SceneManager;
	class Entity;
	class Vector3;
}

class OgreObject {
public:
	OgreObject();
	~OgreObject();
    void addToScene(Ogre::SceneManager *sceneManager, Ogre::Quaternion orientation, Ogre::Vector3 position);
	virtual void load(Ogre::SceneManager *sceneManager) = 0;
	void setScale(Ogre::Vector3 scale);
	void setPosition(Ogre::Vector3 position);
	Ogre::Vector3 getPosition() const;
	Ogre::SceneNode* getSceneNode() const { return mSceneNode; }
	Ogre::Entity* getEntity() const { return mEntity; }
	Ogre::Vector3 getDirection() const;
	void setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z) { mSceneNode->setOrientation(w, x, y, z); }
	Ogre::Quaternion getOrientation() const;

protected:
	void setEntity(Ogre::Entity *entity) { mEntity = entity; }
	Ogre::SceneNode *mSceneNode;
	Ogre::Entity *mEntity;
	
};

#endif