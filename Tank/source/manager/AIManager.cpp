#include "include\manager\AIManager.h"
#include "include\core\World.h"
#include "include\object\tank\Tank.h"
#include "include\object\OgreObject.h"
#include "include\object\PhysicsObject.h"
#include "include\object\projectile\Shell.h"

#include "btBulletDynamicsCommon.h"
#include "Ogre.h"
#include <set>

AIManager::AIManager(World *world) {
	mWorld = world;
}

AIManager::~AIManager() {
}

void AIManager::think(float time) {
	std::set<Tank*>& aiPlayers = mWorld->getAIPlayers();
	std::set<Tank*>::iterator it = aiPlayers.begin();
	while (it != aiPlayers.end()) {	
		Tank *tank = *it;
		move(tank, time);
		it++;
	}
}

void AIManager::move(Tank *tank, float time) {
	Tank* humanPlayer = mWorld->getHumanPlayer();
	btVector3 humanPlayerPos = humanPlayer->getPhysicsObject()->getPosition();
	btVector3 aiPlayerPos = tank->getPhysicsObject()->getPosition();
	btScalar distance = aiPlayerPos.distance(humanPlayerPos);
	btScalar angle = aiPlayerPos.angle(humanPlayerPos);
	if (distance < 50) {
	    if (tank->isShellEnabled()) {
		    mWorld->addProjectile(tank->fireShell(mWorld));
		}
	} 
	tank->move(time);
	if (angle < 0) {
		tank->yaw(-time);
	} else {
	    tank->yaw(time);
	}
	tank->update();
}