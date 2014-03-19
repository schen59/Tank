#ifndef __OgreWall_h_
#define __OgreWall_h_

#include "include\object\OgreObject.h"

class OgreObject;

class OgreWall : public OgreObject {
public:
	OgreWall();
	~OgreWall();
	void load(Ogre::SceneManager *sceneManager);
};

#endif