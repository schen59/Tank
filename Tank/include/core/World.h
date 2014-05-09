#ifndef __World_h_
#define __World_h_

#include "include\object\AbstractObject.h"

#include "Ogre.h"
#include <vector>
#include "btBulletDynamicsCommon.h"

namespace Ogre {
	class SceneManager;
	class Overlay;
}

class Tank;
class Ground;
class InputHandler;
class OgreWorld;
class PhysicsWorld;
class Wall;
class Projectile;
class AbstractObject;
class AIManager;
class SoundManager;
class Health;

class World {
public:
	World(InputHandler *inputHandler);
	~World();
	void setup(Ogre::SceneManager *sceneManager, btVector3 &gravity);
	Tank* getHumanPlayer() const { return mHumanPlayer; }
	OgreWorld* getOgreWorld() const { return mOgreWorld; }
	PhysicsWorld* getPhysicsWorld() const { return mPhysicsWorld; }
	void think(float time);
    std::set<Tank*>& getAIPlayers() { return mAIPlayers; }
	void createAIPlayers();
	void addProjectile(Projectile *projectile);
	void removeObject(AbstractObject *object);
	int score;
	//int timer;
private:
	void createHumanPlayer();
	void createGround();
	void createBoundaryWalls();
	void createObstacles();
	void createHealthPowerups();
	void updateHumanPlayer(float time);
	void updateProjectiles(float time);
	btVector3 getRandomPoint();
	void updateObstacles();
	void updateAIPlayers(float time);

	OgreWorld *mOgreWorld;
	PhysicsWorld *mPhysicsWorld;
	Tank *mHumanPlayer;
	Health *mHealthPowerup;
	std::set<AbstractObject*> mObstacles;
	std::set<Projectile*> mProjectiles;
	std::set<Tank*> mAIPlayers;
	AIManager *mAIManager;
	SoundManager *mSoundManager;
	InputHandler *mInputHandler;
	Ogre::Overlay *mOverlay;
	Ogre::Overlay *mmOverlay;
	Ogre::Overlay *mmmOverlay;
	float timer;
};

#endif