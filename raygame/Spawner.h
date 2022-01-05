#pragma once
#include "Actor.h"
#include "Transform2D.h"

class Spawner:
	public Actor
{
public:	
	Spawner(float x, float y, const char* name = "Actor");
	~Spawner();

	void update(float deltaTime) override;

private:
	float m_numberofenemies = 0;
	float m_timesincelastSpawn;
	float m_spawnCooldown = 2;

	Actor* m_enemyspawn;
};

