#include "include\core\World.h"
#include "include\tank\Tank.h"
#include "include\wall\Wall.h"
#include "include\ground\Ground.h"
#include "include\handler\InputHandler.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\factory\ObjectFactory.h"
#include "include\projectile\Projectile.h"
#include "include\tank\OgreTank.h"

#include "OgreSceneManager.h"
#include "btBulletDynamicsCommon.h"
#include "Ogre.h"
#include <vector>

World::World(InputHandler *inputHandler) {
	mInputHandler = inputHandler;
}

void World::setup(Ogre::SceneManager *sceneManager, btVector3 &gravity) {
	mOgreWorld = new OgreWorld(sceneManager);
	mPhysicsWorld = new PhysicsWorld(gravity);
	mPhysicsWorld->setup();
	createHumanPlayer();
	createGround();
	createBoundaryWalls();
}

void World::createBoundaryWalls() {
	Wall *leftWall = ObjectFactory::createWall(0, btVector3(2, 20, 200));
	leftWall->addToWorld(this, btQuaternion(0, 0, 0, 1), btVector3(-100, 0, 0));
	Wall *rightWall = ObjectFactory::createWall(0, btVector3(2, 20, 200));
	rightWall->addToWorld(this, btQuaternion(0, 1, 0, 0), btVector3(100, 0, 0));
	Wall *topWall = ObjectFactory::createWall(0, btVector3(200, 20, 2));
	topWall->addToWorld(this, btQuaternion(0, -sqrt(0.5), 0, sqrt(0.5)), btVector3(0, 0, -100));
	Wall *bottomWall = ObjectFactory::createWall(0, btVector3(200, 20, 2));
	bottomWall->addToWorld(this, btQuaternion(0, sqrt(0.5), 0, sqrt(0.5)), btVector3(0, 0, 100));
	mWalls.push_back(topWall);
	mWalls.push_back(bottomWall);
}

void World::createHumanPlayer() {
	mHumanPlayer = ObjectFactory::createTank(0.5, btVector3(1.0, 1.0, 1.0));
	mHumanPlayer->addToWorld(this, btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0));
}

void World::createGround() {
	mGround = ObjectFactory::createGround(0, btVector3(200, 2, 200));
	mGround->addToWorld(this, btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0));
	mGround->setFriction(1.5);
}

void World::think(float time) {
	mPhysicsWorld->think(time);
	mHumanPlayer->update();
	for (std::vector<Projectile*>::iterator it=mProjectiles.begin(); it!=mProjectiles.end(); it++) {
		Projectile *projectile = *it;
		projectile->update();
	}
	if (mInputHandler->isKeyDown(OIS::KC_W)) {
		mHumanPlayer->move(time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_S)) {
		mHumanPlayer->move(-time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_A)) {
		mHumanPlayer->yaw(time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_D)) {
		mHumanPlayer->yaw(-time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_J) && !mInputHandler->wasKeyDown(OIS::KC_J)) {
		Projectile *projectile = mHumanPlayer->fire(this);
		mProjectiles.push_back(projectile);
	}
	if (mInputHandler->isKeyDown(OIS::KC_R)) {
		mHumanPlayer->reset();
	}
	
}

void World::destroyBoundaryWalls() {
	for (std::vector<Wall*>::iterator it=mWalls.begin(); it!=mWalls.end(); it++) {
		Wall *wall = *it;
		delete wall;
	}
}

World::~World() {
	destroyBoundaryWalls();
	delete mHumanPlayer;
}
