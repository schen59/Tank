#ifndef __AIManager_h_
#define __AIManager_h_

class World;
class Tank;

class AIManager {
public:
	AIManager(World *world);
	~AIManager();
	void think(float time);

private:
	void move(Tank *tank, float time);

	World *mWorld;
};

#endif