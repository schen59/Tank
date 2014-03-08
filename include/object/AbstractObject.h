#ifndef __AbstractObject_h_
#define __AbstractObject_h_

#include "Ogre.h"

namespace Ogre {
	class SceneNode;
	class Entity;
	class Vector3;
}

class AbstractObject {
public:
	AbstractObject();
	~AbstractObject();
	virtual void addToScene(Ogre::SceneNode *parentSceneNode);
	virtual void load() = 0;
	void setScale(Ogre::Vector3 scale);
	void setPosition(Ogre::Vector3 position);
	Ogre::SceneNode* getSceneNode() const { return mSceneNode; }
	Ogre::Vector3 getDirection() const;
	void setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z) { mSceneNode->setOrientation(w, x, y, z); }

protected:
	void setEntity(Ogre::Entity *entity) { mEntity = entity; }

private:
	Ogre::Quaternion getOrientation() const; 

	Ogre::SceneNode *mSceneNode;
	Ogre::Entity *mEntity;
};

#endif