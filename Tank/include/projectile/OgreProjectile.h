#ifndef __OgreProjectile_h_
#define __OgreProjectile_h_

#include "include\object\OgreObject.h"

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreProjectile : public OgreObject {
public:
	OgreProjectile();
	~OgreProjectile();
	void load(Ogre::SceneManager *sceneManager);
};

#endif