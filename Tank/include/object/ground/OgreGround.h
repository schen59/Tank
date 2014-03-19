#ifndef __OgreGround_h_
#define __OgreGround_h_

#include "include\object\OgreObject.h"

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreGround : public OgreObject {
public:
	OgreGround();
	~OgreGround();
	void load(Ogre::SceneManager *sceneManager);
};

#endif