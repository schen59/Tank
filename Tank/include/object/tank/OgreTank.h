#ifndef __OgreTank_h_
#define __OgreTank_h_

#include "include\object\OgreObject.h"

class OgreObject;
class OgreWorld;

namespace Ogre {
	class SceneManager;
	class Billboard;
}

class OgreTank : public OgreObject {
public:
	OgreTank();
	~OgreTank();
	void load(Ogre::SceneManager *sceneManager);
	void explode(OgreWorld *ogreWorld);
	Ogre::SceneNode* getBarrelSceneNode()const { return mBarrelSceneNode; }
	void yawBarrel(float degree) const;
	void pitchBarrel(float degree) const;
	Ogre::Vector3 getBarrelWorldPosition();
	void updateHealthBar(float health);

private:
	void loadBody(Ogre::SceneManager *sceneManager);
	void loadBarrel(Ogre::SceneManager *sceneManager);
	void loadHealthBar(Ogre::SceneManager *sceneManager);
	bool mIsExploded;
	Ogre::SceneNode *mBarrelSceneNode;
	Ogre::Billboard *mHealthBar;
};

#endif