#ifndef __World_h_
#define __World_h_

#include "Ogre.h"
#include <vector>
#include "btBulletDynamicsCommon.h"

namespace Ogre {
	class SceneManager;
}

class Tank;
class Ground;
class InputHandler;
class OgreWorld;
class PhysicsWorld;
class Wall;
class Projectile;

class World {
public:
	World(InputHandler *inputHandler);
	~World();
	void setup(Ogre::SceneManager *sceneManager, btVector3 &gravity);
	Tank* getHumanPlayer() const { return mHumanPlayer; }
	OgreWorld* getOgreWorld() const { return mOgreWorld; }
	PhysicsWorld* getPhysicsWorld() const { return mPhysicsWorld; }
	void think(float time);

private:
	void createHumanPlayer();
	void createGround();
	void createBoundaryWalls();
	void destroyBoundaryWalls();

	OgreWorld *mOgreWorld;
	PhysicsWorld *mPhysicsWorld;
	Tank *mHumanPlayer;
	Ground *mGround;
	std::vector<Wall*> mWalls;
	std::vector<Projectile*> mProjectiles;
	InputHandler *mInputHandler;
};

#endif