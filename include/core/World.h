#ifndef __World_h_
#define __World_h_

#include "include\object\AbstractObject.h"
#include "include\object\Tank.h"
#include "include\handler\InputHandler.h"
#include "include\object\Wall.h"
#include "include\object\Ground.h"

#include "Ogre.h"
#include <vector>

namespace Ogre {
	class SceneManager;
}

class AbstractObject;
class Tank;
class InputHandler;
class Wall;
class Ground;

class World {
public:
	World(Ogre::SceneManager *sceneManager, InputHandler *inputHandler);
	~World();
	void setup();
	Tank* getHumanPlayer() const { return mHumanPlayer; }
	void think(Ogre::Real time);

private:
	void createFloor();
	void createGround();
	void createHumanPlayer();
	void createBoundaryWalls();
    void destroyBoundaryWalls();

	Ground *mGround;
	Tank *mHumanPlayer;
	InputHandler *mInputHandler;
	Ogre::SceneManager *mSceneManager;
	std::vector<Wall*> mWalls;
};

#endif