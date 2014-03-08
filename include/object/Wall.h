#ifndef __Wall_h_
#define __Wall_h_

#include "include\object\AbstractObject.h"

namespace Ogre {
	class SceneManager;
}

class AbstractObject;

class Wall : public AbstractObject {
public:
	Wall(Ogre::SceneManager *sceneManager);
	~Wall();
	void load();

private:
	Ogre::SceneManager *mSceneManager;
};

#endif