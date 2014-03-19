#ifndef __OgreTank_h_
#define __OgreTank_h_

#include "include\object\OgreObject.h"

class OgreObject;
class OgreWorld;

namespace Ogre {
	class SceneManager;
}

class OgreTank : public OgreObject {
public:
	OgreTank();
	~OgreTank();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);

private:
	bool mIsExploded;
};

#endif