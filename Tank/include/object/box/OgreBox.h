#ifndef __OgreBox_h_
#define __OgreBox_h_

#include "include\object\OgreObject.h"

namespace Ogre {
	class SceneManager;
}

class OgreObject;

class OgreBox : public OgreObject {
public:
	OgreBox();
	~OgreBox();
	void load(Ogre::SceneManager *sceneManager);
};

#endif