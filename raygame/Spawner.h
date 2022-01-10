#pragma once
#include "Actor.h"
#include "Transform2D.h"
class Player;

class Spawner:
	public Actor
{
public:	
	Spawner(float x, float y, const char* name, Player* player) : Actor(x, y, name) { m_currentplayer = player; }
	~Spawner();

	float getnumberofenemies() { return m_numberofenemies; }
	void setnumberofenemies() { m_numberofenemies = m_numberofenemies; } 

	void update(float deltaTime) override;

private:
	float m_numberofenemies = 0;
	float m_timesincelastSpawn;
	float m_spawnCooldown = 2;

	Actor* m_enemyspawn;
	Player* m_currentplayer;
};

