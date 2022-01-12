#include "Spawner.h"
#include "Engine.h"
#include "Enemy.h"
#include "Transform2D.h"
#include "Player.h"

void Spawner::start()
{
	Actor::start();

;	//Adds Enemy
	Enemy* initSword = new Enemy(700, 700, "Enemy", "Sword", Spawner::m_currentPlayer);
	Enemy* initRusher = new Enemy(50, 500, "Enemy", "Rusher", Spawner::m_currentPlayer);

	//Adds them to spawner
	initSword->setSpawner(this);
	initRusher->setSpawner(this);

	//Adds them to scene
	Engine::getCurrentScene()->addActor(initSword);
	Engine::getCurrentScene()->addActor(initRusher);

	//Increments enemy counter
	m_numberOfEnemies++;
	m_numberOfEnemies++;
}

void Spawner::update(float deltaTime)
{
	m_timeSinceLastSpawn += deltaTime;

	if (m_numberOfEnemies < 7  && m_timeSinceLastSpawn > 2)
	{
		//Declares the enemy that wil be spawned
			m_enemySpawn = new Enemy(50, 100, "Enemy", "Rusher", Spawner::m_currentPlayer);
			m_enemySpawn->getTransform()->setScale({ 50,50 });
			m_enemySpawn->setSpawner(this);

			//Adds that enemy to the game
			Engine::getCurrentScene()->addActor(m_enemySpawn);
			m_timeSinceLastSpawn = 0;//resets the time since last spawn	

			//Declares the enemy that wil be spawned
			m_enemySpawn = new Enemy(750, 100, "Enemy", "Sword", Spawner::m_currentPlayer);
			m_enemySpawn->getTransform()->setScale({ 50,50 });
			m_enemySpawn->setSpawner(this);

			//Adds that enemy to the game
			Engine::getCurrentScene()->addActor(m_enemySpawn);
			m_timeSinceLastSpawn = 0;//resets the time since last spawn	
			m_numberOfEnemies++;//Adds to the number of enemys
			m_numberOfEnemies++;//Adds to the number of enemys
	}
}
