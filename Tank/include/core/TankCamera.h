#ifndef __TankCamera_h_
#define __TankCamera_h_

namespace Ogre {
	class Camera;
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