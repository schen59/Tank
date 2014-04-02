#ifndef __OgreSoccer_h_
#define __OgreSoccer_h_

#include "include\object\OgreObject.h"

class OgreWorld;

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreSoccer : public OgreObject {
public:
	OgreSoccer();
	~OgreSoccer();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);

private:
	bool mIsExploded;
};

#endif