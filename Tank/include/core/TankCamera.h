#ifndef __TankCamera_h_
#define __TankCamera_h_

namespace Ogre {
	class Camera;
}

class Tank;

class TankCamera {
public:
	TankCamera(Ogre::Camera *camera);
	~TankCamera();
	void follow(Tank *tank);
	Ogre::Camera* getCamera() const { return mCamera; }

private:
	Ogre::Camera *mCamera;
};

#endif