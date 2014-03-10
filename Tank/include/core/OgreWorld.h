#ifndef __OgreWorld_h_
#define __OgreWorld_h_

namespace Ogre {
	class SceneManager;
}

class OgreWorld {
public:
	OgreWorld(Ogre::SceneManager *sceneManager);
	~OgreWorld();
	Ogre::SceneManager* getSceneManager() const { return mSceneManager; }

private:
	Ogre::SceneManager *mSceneManager;
};

#endif