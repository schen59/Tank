#include "include\core\World.h"
#include "include\object\Tank.h"
#include "include\handler\InputHandler.h"
#include "include\object\Ground.h"
#include "include\factory\ObjectFactory.h"

#include "OgreSceneManager.h"
#include "Ogre.h"

World::World(Ogre::SceneManager *sceneManager, InputHandler *inputHandler) {
	mSceneManager = sceneManager;
	mInputHandler = inputHandler;
}

void World::setup() {
	//createGround();
	createHumanPlayer();
	createBoundaryWalls();
}

void World::createGround() {
	mGround = ObjectFactory::createGround(mSceneManager);
	mGround->addToScene(mSceneManager->getRootSceneNode());
}

void World::createBoundaryWalls() {
	Wall *leftWall = ObjectFactory::createWall(mSceneManager);
	leftWall->addToScene(mSceneManager->getRootSceneNode());
	leftWall->setPosition(Ogre::Vector3(-100, 0, 0));

	Wall *rightWall = ObjectFactory::createWall(mSceneManager);
	rightWall->addToScene(mSceneManager->getRootSceneNode());
	rightWall->setOrientation(0, 0, 0, 1);
	rightWall->setPosition(Ogre::Vector3(100, 0, 0));

	Wall *topWall = ObjectFactory::createWall(mSceneManager);
	topWall->addToScene(mSceneManager->getRootSceneNode());
	topWall->setOrientation(sqrt(0.5), 0, -sqrt(0.5), 0);
	topWall->setPosition(Ogre::Vector3(0, 0, -100));

	Wall *bottomWall = ObjectFactory::createWall(mSceneManager);
	bottomWall->addToScene(mSceneManager->getRootSceneNode());
	bottomWall->setOrientation(sqrt(0.5), 0, sqrt(0.5), 0);
	bottomWall->setPosition(Ogre::Vector3(0, 0, 100));

	mWalls.push_back(leftWall);
	mWalls.push_back(rightWall);
	mWalls.push_back(topWall);
	mWalls.push_back(bottomWall);
}

void World::createHumanPlayer() {
	mHumanPlayer = ObjectFactory::createTank(mSceneManager);
	mHumanPlayer->addToScene(mSceneManager->getRootSceneNode());
}

void World::think(Ogre::Real time) {
	if (mInputHandler->isKeyDown(OIS::KC_W)) {
		mHumanPlayer->moveForward(time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_S)) {
		mHumanPlayer->moveBackward(time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_A)) {
		mHumanPlayer->yaw(time);
	}
	if (mInputHandler->isKeyDown(OIS::KC_D)) {
		mHumanPlayer->yaw(-time);
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
	//delete mGround;
	delete mHumanPlayer;
}
