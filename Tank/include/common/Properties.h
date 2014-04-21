#ifndef __Properties_h_
#define __Properties_h_

#include "btBulletDynamicsCommon.h"

class Properties {
public:
	enum ObjectType
	{
		GROUND,
		WALL,
		OBSTACLE,
		PROJECTILE,
		TANK,
	};

	enum MenuCommand {
		NEWGAME_EASY,
		NEWGAME_HARD,
		CANCLE,
		QUIT,
	};

	static float GROUND_MASS;
	static btVector3 GROUND_SIZE;
	static btVector3 GROUND_POSITION;
	static btQuaternion GROUND_ORIENTATION;
	static float GROUND_FRICTION;
	static btQuaternion IDENTITY;

	static float WALL_MASS;
	static btVector3 LEFT_WALL_POSITION;
	static btVector3 LEFT_WALL_SIZE;
	static btVector3 RIGHT_WALL_POSITION;
	static btVector3 RIGHT_WALL_SIZE;
	static btVector3 TOP_WALL_POSITION;
	static btVector3 TOP_WALL_SIZE;
	static btVector3 BOTTOM_WALL_POSITION;
	static btVector3 BOTTOM_WALL_SIZE;
	static btQuaternion LEFT_WALL_ORIENTATION;
	static btQuaternion RIGHT_WALL_ORIENTATION;
	static btQuaternion TOP_WALL_ORIENTATION;
	static btQuaternion BOTTOM_WALL_ORIENTATION;

	static float TANK_MASS;
	static btVector3 TANK_SIZE;
	static btQuaternion TANK_ORIENTATION;

	static float BOX_MASS;
	static btVector3 BOX_SIZE;
	static btQuaternion BOX_ORIENTATION;

	static btVector3 HUMAN_PLAYER_POSITION;

private:
	Properties();
	~Properties();
};

#endif