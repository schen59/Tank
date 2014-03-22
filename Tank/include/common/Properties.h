#ifndef __Properties_h_
#define __Properties_h_

class Properties {
public:
	enum ObjectType
	{
		GROUND,
		WALL,
		OBSTACLE,
		PROJECTILE,
		TANK,
		MISSILE
	};

private:
	Properties();
	~Properties();
};

#endif