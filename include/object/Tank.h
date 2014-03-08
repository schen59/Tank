#ifndef __Tank_h_
#define __Tank_h_

#include "Ogre.h"

#include "include\object\AbstractObject.h"

namespace Ogre {
	class SceneNode;
	class SceneManager;
}

class AbstractObject;

class Tank : public AbstractObject {
public:
	Tank(Ogre::SceneManager *sceneManager);
	~Tank();
	void load();
	void moveForward(Ogre::Real time);
	void moveBackward(Ogre::Real time);
	void yaw(Ogre::Real time);

private:
	Ogre::Real mSpeed;
	Ogre::SceneManager *mSceneManager;
};

#endif