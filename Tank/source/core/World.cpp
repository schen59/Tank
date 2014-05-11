#include "include\core\World.h"
#include "include\object\tank\Tank.h"
#include "include\object\wall\Wall.h"
#include "include\object\ground\Ground.h"
#include "include\object\box\Box.h"
#include "include\handler\InputHandler.h"
#include "include\core\OgreWorld.h"
#include "include\core\PhysicsWorld.h"
#include "include\factory\ObjectFactory.h"
#include "include\object\projectile\Shell.h"
#include "include\object\projectile\Missile.h"
#include "include\object\projectile\Soccer.h"
#include "include\object\projectile\Projectile.h"
#include "include\object\tank\OgreTank.h"
#include "include\object\projectile\PhysicsShell.h"
#include "include\object\projectile\PhysicsMissile.h"
#include "include\object\projectile\PhysicsSoccer.h"
#include "include\object\AbstractObject.h"
#include "include\manager\AIManager.h"
#include "include\manager\SoundManager.h"
#include "include\common\Properties.h"
#include "include\object\powerup\Health.h"

#include "OgreSceneManager.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "btBulletDynamicsCommon.h"
#include "Ogre.h"
#include <vector>

World::World(InputHandler *inputHandler) {
	mInputHandler = inputHandler;
	mScore = 0;
	mGameTime = 0;
	mIsHard = false;
}

void World::setup(Ogre::SceneManager *sceneManager, btVector3 &gravity, bool isHard) {
	mIsHard = isHard;
	mOgreWorld = new OgreWorld(sceneManager);
	mPhysicsWorld = new PhysicsWorld(gravity);
	mAIManager = new AIManager(this);
	mSoundManager = new SoundManager();
	mPhysicsWorld->setup();
	createHumanPlayer();
	createGround();
	createBoundaryWalls();
	createObstacles();
	if (isHard == true) {
	    createAIPlayers(7);
	} else {
		createAIPlayers(5);
	}
	createHealthPowerups();
	createOverlay();
}

void World::createOverlay() {
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	mWeaponOverlay = om.getByName("ShellOverlay");
	mWeaponOverlay->show();
	Ogre::OverlayManager& omm = Ogre::OverlayManager::getSingleton();
	mScoreOverlay = omm.getByName("ScoreOverlay");
	mScoreOverlay->show();
	//Ogre::OverlayManager& ommm = Ogre::OverlayManager::getSingleton();
	//mmmOverlay = ommm.getByName("CrosshairOverlay");
	//mmmOverlay->show();
}

void World::createHealthPowerups() {
	mHealthPowerup = ObjectFactory::createHealthPowerup();
	mOgreWorld->addObject(mHealthPowerup, Ogre::Quaternion(0, 0, 0, 1), Ogre::Vector3(0, 0, 10));
}

void World::createBoundaryWalls() {
	Wall *leftWall = ObjectFactory::createWall(Properties::WALL_MASS, Properties::LEFT_WALL_SIZE);
	leftWall->addToWorld(this, Properties::LEFT_WALL_ORIENTATION, Properties::LEFT_WALL_POSITION);
	Wall *rightWall = ObjectFactory::createWall(Properties::WALL_MASS, Properties::RIGHT_WALL_SIZE);
	rightWall->addToWorld(this, Properties::RIGHT_WALL_ORIENTATION, Properties::RIGHT_WALL_POSITION);
	Wall *topWall = ObjectFactory::createWall(Properties::WALL_MASS, Properties::TOP_WALL_SIZE);
	topWall->addToWorld(this, Properties::TOP_WALL_ORIENTATION, Properties::TOP_WALL_POSITION);
	Wall *bottomWall = ObjectFactory::createWall(Properties::WALL_MASS, Properties::BOTTOM_WALL_SIZE);
	bottomWall->addToWorld(this, Properties::BOTTOM_WALL_ORIENTATION, Properties::BOTTOM_WALL_POSITION);
}

btVector3 World::getRandomPoint() {
	int x = -50 + rand() % 100;
	int y = rand() % 50;
	int z = -50 + rand() % 100;
	return btVector3(x, y, z);
}

void World::createAIPlayers(int number) {
	for (int i=0; i<number; i++) {
		Tank *tank = ObjectFactory::createTank(Properties::TANK_MASS, Properties::TANK_SIZE);
		tank->addToWorld(this, Properties::TANK_ORIENTATION, getRandomPoint());
		mAIPlayers.insert(tank);
	}
}

void World::createObstacles() {
	for (int i=0; i<10; i++) {
		Box *box = ObjectFactory::createBox(Properties::BOX_MASS, Properties::BOX_SIZE);
		box->addToWorld(this, Properties::BOX_ORIENTATION, getRandomPoint());
		mObstacles.insert(box);
	}
}

void World::createHumanPlayer() {
	mHumanPlayer = ObjectFactory::createTank(Properties::TANK_MASS, Properties::TANK_SIZE);
	mHumanPlayer->addToWorld(this, Properties::TANK_ORIENTATION, Properties::HUMAN_PLAYER_POSITION);
}

void World::createGround() {
	Ground *ground = ObjectFactory::createGround(Properties::GROUND_MASS, Properties::GROUND_SIZE);
	ground->addToWorld(this, Properties::GROUND_ORIENTATION, Properties::GROUND_POSITION);
	ground->setFriction(Properties::GROUND_FRICTION);
}

void World::updateHumanPlayer(float time) {
	mHumanPlayer->update();
	
	//Ogre::LogManager::getSingleton().logMessage("isMouseDown " + Ogre::StringConverter::toString(mInputHandler->isMouseDown(OIS::MB_Left)));
	if (mInputHandler->isMouseDown(OIS::MB_Left)) {
		if (mHumanPlayer->isShellEnabled()) {
		    addProjectile(mHumanPlayer->fireShell(this));
			mSoundManager->playFireSound();
		}
	}
	if (mInputHandler->isMouseDown(OIS::MB_Right)) {
		mHumanPlayer->pitchBarrel(time);
		mSoundManager->playMoveSound();
	}
	if (mInputHandler->isMouseMoveLeft()) {
		mHumanPlayer->yawBarrel(time);
		mSoundManager->playMoveSound();
	}
	if (mInputHandler->isMouseMoveRight()) {
		mHumanPlayer->yawBarrel(-time);
		mSoundManager->playMoveSound();
	}
	if (mInputHandler->isMouseDown(OIS::MB_Middle)) {
		if (mHumanPlayer->isSoccerEnabled()) {
			addProjectile(mHumanPlayer->fireSoccer(this));
			mSoundManager->playSpecialFireSound();
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_W)) {
		mHumanPlayer->move(time);
		mSoundManager->playMoveSound();
	}
	if (mInputHandler->isKeyDown(OIS::KC_S)) {
		mHumanPlayer->move(-time);
		mSoundManager->playMoveSound();
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
		if (mHumanPlayer->isShellEnabled()) {
		    addProjectile(mHumanPlayer->fireShell(this));
			mSoundManager->playFireSound();
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_K) && !mInputHandler->wasKeyDown(OIS::KC_K)) {
		if (mHumanPlayer->isMissileEnabled()) {
			addProjectile(mHumanPlayer->fireMissile(this));
			mSoundManager->playFireSound();
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_L) && !mInputHandler->wasKeyDown(OIS::KC_L)) {
		if (mHumanPlayer->isSoccerEnabled()) {
			addProjectile(mHumanPlayer->fireSoccer(this));
			mSoundManager->playSpecialFireSound();
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_SPACE)) {
		Ogre::Vector3 healthPowerupPos = mHealthPowerup->getPosition();
		Ogre::Vector3 humanPlayerPos = mHumanPlayer->getOgreObject()->getPosition();
		if (healthPowerupPos.distance(humanPlayerPos) < 10) {
			mHumanPlayer->increaseHealth();
		}
	}
	if (mInputHandler->isKeyDown(OIS::KC_Y) && !mInputHandler->wasKeyDown(OIS::KC_Y)) {
		mHumanPlayer->toggleLight(this);
	}
	if (mHumanPlayer->isCollided()) {
		mHumanPlayer->attacked();
	}
}

void World::addProjectile(Projectile *projectile) {
	mProjectiles.insert(projectile);
	//mSoundManager->playFireSound();
}

void World::updateProjectiles(float time) {
	std::set<Projectile*>::iterator it=mProjectiles.begin(); 
	while (it != mProjectiles.end()) {
		Projectile *projectile = *it;
		if (projectile->isCollided() && !projectile->isExploded()) {
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

void World::removeObject(AbstractObject *object) {
	mPhysicsWorld->removeObject(object->getPhysicsObject());
	mOgreWorld->removeObject(object->getOgreObject());
	delete object;
}

void World::think(float time) {
	mGameTime += time;
	mPhysicsWorld->think(time);
	mAIManager->think(time);
	updateObstacles();
	updateAIPlayers(time);
	updateHumanPlayer(time);
	updateProjectiles(time);
	if (mIsHard == false) {
	    mOgreWorld->setLight(mGameTime);
	}
	updateOverlay();
}

void World::updateOverlay() {
	Ogre::OverlayManager& omm = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *text = (Ogre::TextAreaOverlayElement *) omm.getOverlayElement("ScorePanel/Text");
	text->setCaption("Score: " + Ogre::StringConverter::toString(mScore));
	Ogre::TextAreaOverlayElement *gameTime = (Ogre::TextAreaOverlayElement *) omm.getOverlayElement("ScorePanel/Timer");
	gameTime->setCaption("Time: " + Ogre::StringConverter::toString(mGameTime));
}

void World::updateObstacles() {
	for (std::set<AbstractObject*>::iterator it=mObstacles.begin(); it!=mObstacles.end(); it++) {
		AbstractObject *object = *it;
		object->update();
	}
}

void World::updateAIPlayers(float time) {
	if (mAIPlayers.size() == 0) {
		createAIPlayers(5);
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
			mScore++;
		}
	}
}

World::~World() {
	delete mOgreWorld;
	delete mPhysicsWorld;
	delete mAIManager;
	delete mSoundManager;
	delete mHumanPlayer;
}
