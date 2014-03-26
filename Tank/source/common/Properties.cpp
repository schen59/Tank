#include "include\common\Properties.h"

#include "btBulletDynamicsCommon.h"

Properties::Properties() {}

Properties::~Properties() {}

btQuaternion Properties::IDENTITY = btQuaternion(0, 0, 0, 1);
float Properties::GROUND_MASS = 0;
float Properties::WALL_MASS = 0;

btVector3 Properties::GROUND_SIZE = btVector3(200, 2, 200);
btVector3 Properties::GROUND_POSITION = btVector3(0, -1, 0);
btQuaternion Properties::GROUND_ORIENTATION = Properties::IDENTITY;
float Properties::GROUND_FRICTION = 1.5;

btVector3 Properties::LEFT_WALL_SIZE = btVector3(2, 20, 200);
btVector3 Properties::LEFT_WALL_POSITION = btVector3(-100, 0, 0);
btQuaternion Properties::LEFT_WALL_ORIENTATION = Properties::IDENTITY;
btVector3 Properties::RIGHT_WALL_SIZE = btVector3(2, 20, 200);
btQuaternion Properties::RIGHT_WALL_ORIENTATION = btQuaternion(0, 1, 0, 0);
btVector3 Properties::RIGHT_WALL_POSITION = btVector3(100, 0, 0);
btVector3 Properties::TOP_WALL_SIZE = btVector3(200, 20, 2);
btQuaternion Properties::TOP_WALL_ORIENTATION = btQuaternion(0, -sqrt(0.5), 0, sqrt(0.5));
btVector3 Properties::TOP_WALL_POSITION = btVector3(0, 0, -100);
btVector3 Properties::BOTTOM_WALL_SIZE = btVector3(200, 20, 2);
btQuaternion Properties::BOTTOM_WALL_ORIENTATION = btQuaternion(0, sqrt(0.5), 0, sqrt(0.5));
btVector3 Properties::BOTTOM_WALL_POSITION = btVector3(0, 0, 100);

float Properties::TANK_MASS = 1;
btVector3 Properties::TANK_SIZE = btVector3(4.0, 2.0, 4.0);
btQuaternion Properties::TANK_ORIENTATION = Properties::IDENTITY;

float Properties::BOX_MASS = 0.1;
btVector3 Properties::BOX_SIZE = btVector3(2.0, 2.0, 2.0);
btQuaternion Properties::BOX_ORIENTATION = Properties::IDENTITY;

btVector3 Properties::HUMAN_PLAYER_POSITION = btVector3(0, 0, 0);



