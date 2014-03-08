#ifndef __TankApp_h_
#define __TankApp_h_

#include "Ogre.h"

namespace Ogre {
	class Root;
}
class TankManager;

class TankApp {
public:
	TankApp();
	~TankApp();
	bool setup();
	void go();

private:
	void setupRoot();
	void setupResources();
	void setupTankManager();
	bool configure();

	Ogre::String mResourcePath;
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mWindow;
	TankManager *mTankManager;
};

#endif