#ifndef __OgreShell_h_
#define __OgreShell_h_

#include "include\object\OgreObject.h"

class OgreWorld;

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreShell : public OgreObject {
public:
	OgreShell();
	~OgreShell();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);

};

#endif