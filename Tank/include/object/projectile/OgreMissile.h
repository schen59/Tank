#ifndef __OgreMissile_h_
#define __OgreMissile_h_

#include "include\object\OgreObject.h"

class OgreWorld;

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreMissile : public OgreObject {
public:
	OgreMissile();
	~OgreMissile();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);

private:
	bool mIsExploded;
};

#endif