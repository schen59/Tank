#ifndef __OgreTank_h_
#define __OgreTank_h_

#include "include\object\OgreObject.h"

class OgreObject;
class OgreWorld;

namespace Ogre {
	class SceneManager;
	class Billboard;
	class Light;
}

class OgreTank : public OgreObject {
public:
	OgreTank();
	~OgreTank();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);
	Ogre::SceneNode* getBarrelSceneNode()const { return mBarrelSceneNode; }
	void yawBarrel(float degree);
	void pitchBarrel(float degree);
	Ogre::Vector3 getBarrelWorldPosition();
	void updateHealthBar(float health);
	void toggleLight(OgreWorld *ogreWorld);

private:
	void loadBody(Ogre::SceneManager *sceneManager);
	void loadBarrel(Ogre::SceneManager *sceneManager);
	void loadHealthBar(Ogre::SceneManager *sceneManager);
	void loadLight(Ogre::SceneManager *sceneManager);
	void updateLight();
	bool mIsExploded;
	bool mIsLightOn;
	Ogre::SceneNode *mBarrelSceneNode;
	Ogre::Billboard *mHealthBar;
	Ogre::Light *mLight;
};

#endif