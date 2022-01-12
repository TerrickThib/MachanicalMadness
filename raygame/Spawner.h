#pragma once
#include "Actor.h"
#include "Transform2D.h"
class Enemy;
class Player;

class Spawner:
	public Actor
{
public:	
	Spawner(float x, float y, const char* name, Player* player) : Actor(x, y, name) { m_currentPlayer = player; }
	~Spawner();

	float getNumberOfEnemies() { return m_numberOfEnemies; }
	void setNumberOfEnemies(float newEnemyCount) { m_numberOfEnemies = newEnemyCount; }

	void start() override;
	void update(float deltaTime) override;

private:
	float m_numberOfEnemies = 0;
	float m_timeSinceLastSpawn;

	Enemy* m_enemySpawn;
	Player* m_currentPlayer;
};

