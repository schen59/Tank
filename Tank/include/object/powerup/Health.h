#ifndef __Health_h__
#define __Health_h__

#include "include\object\OgreObject.h"

namespace Ogre {
	class SceneManager;
}
class OgreObject;

class Health : public OgreObject {
public:
	Health();
	~Health();
	void load(Ogre::SceneManager *sceneManager);
};

#endif