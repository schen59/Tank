#include "include\core\World.h"
#include "include\object\tank\Tank.h"
#include "include\object\wall\Wall.h"
#include "include\object\ground\Ground.h"
#include "include\object\box\Box.h"
#include "include\handler\InputHandler.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\factory\ObjectFactory.h"
#include "include\object\projectile\Projectile.h"
#include "include\object\projectile\Missile.h"
#include "include\object\tank\OgreTank.h"
#include "include\object\projectile\PhysicsProjectile.h"
#include "include\object\projectile\PhysicsMissile.h"
#include "include\object\AbstractObject.h"
#include "include\manager\AIManager.h"
#include "include\manager\SoundManager.h"

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
	mAIManager = new AIManager(this);
	mSoundManager = new SoundManager();
	mPhysicsWorld->setup();
	createHumanPlayer();
	createGround();
	createBoundaryWalls();
	createObstacles();
	createAIPlayers();
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
}

btVector3 World::getRandomPoint() {
	int x = -50 + rand() % 100;
	int y = rand() % 50;
	int z = -50 + rand() % 100;
	return btVector3(x, y, z);
}

void World::createAIPlayers() {
	for (int i=0; i<5; i++) {
		Tank *tank = ObjectFactory::createTank(1, btVector3(4.0, 2.0, 4.0));
		tank->addToWorld(this, btQuaternion(0, 0, 0, 1), getRandomPoint());
		mAIPlayers.insert(tank);
	}
}

void World::createObstacles() {
	for (int i=0; i<10; i++) {
		Box *box = ObjectFactory::createBox(0.1, btVector3(2.0, 2.0, 2.0));
		box->addToWorld(this, btQuaternion(0, 0, 0, 1), getRandomPoint());
		mObstacles.insert(box);
	}
}

void World::createHumanPlayer() {
	mHumanPlayer = ObjectFactory::createTank(1, btVector3(4.0, 2.0, 4.0));
	mHumanPlayer->addToWorld(this, btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0));
}

void World::createGround() {
	Ground *ground = ObjectFactory::createGround(0, btVector3(200, 2, 200));
	ground->addToWorld(this, btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0));
	ground->setFriction(1.5);
}

void World::updateHumanPlayer(float time) {
	mHumanPlayer->update();
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
	if (mInputHandler->isKeyDown(OIS::KC_R)) {
		mHumanPlayer->reset();
	}
	if (mInputHandler->isKeyDown(OIS::KC_J) && !mInputHandler->wasKeyDown(OIS::KC_J)) {
		if (mHumanPlayer->isEnabled()) {
		    addProjectile(mHumanPlayer->fire(this));
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_K) && !mInputHandler->wasKeyDown(OIS::KC_K)) {
		if (mHumanPlayer->isEnabledMissile()) {
		    addMissile(mHumanPlayer->fireMissile(this));
		}
	}
}

void World::addProjectile(Projectile *projectile) {
	mProjectiles.insert(projectile);
	mSoundManager->playFireSound();
}

void World::addMissile(Missile *missile) {
	mMissiles.insert(missile);
	mSoundManager->playExplosionSound();
}

void World::updateProjectiles(float time) {
	std::set<Projectile*>::iterator it=mProjectiles.begin(); 
	while (it != mProjectiles.end()) {
		Projectile *projectile = *it;
		if (projectile->isCollided()) {
			projectile->explode(this);
			mSoundManager->playExplosionSound();
		}
		projectile->update();
		if (!projectile->isActive()) {
			it = mProjectiles.erase(it);
			removeObject(projectile);
		} else {
			it++;
		}
	}
}

void World::updateMissiles(float time) {
	std::set<Missile*>::iterator it=mMissiles.begin(); 
	while (it != mMissiles.end()) {
		Missile *missile = *it;
		if (missile->isCollided()) {
			missile->explode(this);
			mSoundManager->playExplosionSound();
		}
		missile->update();
		if (!missile->isActive()) {
			it = mMissiles.erase(it);
			removeObject(missile);
		} else {
			it++;
		}
	}
}

void World::removeObject(AbstractObject *object) {
	mPhysicsWorld->removeObject(object->getPhysicsObject());
	mOgreWorld->removeObject(object->getOgreObject());
	delete object;
}

void World::think(float time) {
	mPhysicsWorld->think(time);
	mAIManager->think(time);
	updateObstacles();
	updateAIPlayers(time);
	updateHumanPlayer(time);
	updateProjectiles(time);
	updateMissiles(time);
}

void World::updateObstacles() {
	for (std::set<AbstractObject*>::iterator it=mObstacles.begin(); it!=mObstacles.end(); it++) {
		AbstractObject *object = *it;
		object->update();
	}
}

void World::updateAIPlayers(float time) {
	if (mAIPlayers.size() == 0) {
		createAIPlayers();
	}
	std::set<Tank*>::iterator it = mAIPlayers.begin();
	while (it != mAIPlayers.end()) {
		Tank *tank = *it;
		if (tank->isCollided()) {
			tank->attacked();
		}
		if (tank->isAlive()) {
			tank->update();
			it++;
		} else {
			tank->explode(this);
			it = mAIPlayers.erase(it);
			removeObject(tank);
		}
	}
}

World::~World() {
	//destroyBoundaryWalls();
	delete mOgreWorld;
	delete mPhysicsWorld;
	delete mAIManager;
	delete mSoundManager;
	delete mHumanPlayer;
	//delete mHumanPlayer;
}
