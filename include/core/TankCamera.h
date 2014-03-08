#ifndef __TankCamera_h_
#define __TankCamera_h_

#include "include\object\AbstractObject.h"

namespace Ogre {
	class Camera;
	class Vector3;
}

class AbstractObject;

class TankCamera {
public:
	TankCamera(Ogre::Camera *camera);
	~TankCamera();
	void follow(AbstractObject *object);
	Ogre::Camera* getCamera() const { return mCamera; }

private:
	Ogre::Camera *mCamera;
};

#endif