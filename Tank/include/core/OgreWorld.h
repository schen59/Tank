#ifndef __OgreWorld_h_
#define __OgreWorld_h_

#include "Ogre.h"
#include <set>

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreWorld {
public:
	OgreWorld(Ogre::SceneManager *sceneManager);
	~OgreWorld();
	Ogre::SceneManager* getSceneManager() const { return mSceneManager; }
	void addObject(OgreObject *object, Ogre::Quaternion orientation, Ogre::Vector3 position);
	void removeObject(OgreObject *object);

private:
	void destroyObjects();

	Ogre::SceneManager *mSceneManager;
	std::set<OgreObject*> mObjects;
};

#endif