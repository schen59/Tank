#ifndef __Ground_h_
#define __Ground_h_

#include "include\object\AbstractObject.h"

namespace Ogre {
	class SceneManager;
}

class AbstractObject;

class Ground : public AbstractObject {
public:
	Ground(Ogre::SceneManager *sceneManager);
	~Ground();
	void load();

private:
	Ogre::SceneManager *mSceneManager;
};

#endif