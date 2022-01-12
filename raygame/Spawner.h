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

	float getNumberOfEnemies() { return m_numberOfEnemies; }//Gets the number of enemies in the game
	void setNumberOfEnemies(float newEnemyCount) { m_numberOfEnemies = newEnemyCount; }//Sets the number of enemies 

	void start() override;
	void update(float deltaTime) override;

private:
	float m_numberOfEnemies = 0;
	float m_timeSinceLastSpawn;
	float m_spawnCooldown = 2;

	Enemy* m_enemySpawn;
	Player* m_currentPlayer;
};

