#include "Enemy.h"
#include "Engine.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "SwordComponent.h"
#include "Transform2D.h"
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "raylib.h"
#include "Spawner.h"
#include "PowerUp.h"

void Enemy::start()
{
	Actor::start();

	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));//allows asses to move component
	m_moveComponent->setMaxSpeed(1000); ///Sets a max cap for the speed
	//Declares the stats/Varibles for a Rusher enemy
	if (m_type == "Rusher")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Rusher.png")));
		getTransform()->setScale({ 25,25 });
		setCollider(new CircleCollider(10, this));
		m_moveComponent->setSpeed(200);
	}
	////Declares the stats/Varibles for a Gunner enemy
	//else if (m_type == "Gunner")
	//{
	//	m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Gunner.png")));
	//	getTransform()->setScale({ 35,70 });
	//	setCollider(new AABBCollider(this));
	//}
	//Declaes the stats/Varibles for a Sword enemy
	else if (m_type == "Sword")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Sword.png")));
		getTransform()->setScale({ 35,70 });
		setCollider(new AABBCollider(70,70,this));
		m_swordComponent = dynamic_cast<SwordComponent*>(addComponent(new SwordComponent()));
		m_moveComponent->setSpeed(100);
	}
}

void Enemy::update(float deltaTime)
{
	//If your a sword and your not using the sword or your not using the sword you follow the player
	if (m_type == "Sword" && !m_swordComponent->getInUse() || m_type != "Sword")
	{
		Actor::update(deltaTime);

		MathLibrary::Vector2 moveDirection = (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getNormalized();
		getTransform()->setForward(moveDirection);

		//Multiplys the movedirection with current speed to get Velocity
		m_moveComponent->setVelocity(moveDirection * m_moveComponent->getSpeed());
	}
	
	//If there is a sword and your close enough to the player swing sword
	if (m_type == "Sword" && (getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).getMagnitude() < 75 && !m_swordComponent->getInUse())
	{
		m_swordComponent->swingSword();
	}

	if(m_type == "Sword")
	m_swordComponent->update(deltaTime);
}

void Enemy::onCollision(Actor* other)
{
	//If enemy collides with players sword
	if (other->getName() == "PlayerSword")
	{
		//Have a chance to drop a Power Up
		if (m_type == "Rusher")
		{
			int dropChance = rand() % 101;
			if (dropChance <= 10 || Engine::getKeyDown(KEY_P))
			{
				//Declares the Power ups Varibles and Adds the POwer up to Current Scene
				Actor* swordUpgrade = new Actor(getTransform()->getLocalPosition().x, getTransform()->getLocalPosition().y, "SpinBlade");
				swordUpgrade->addComponent(new SpriteComponent("Images/Powerup.png"));
				swordUpgrade->getTransform()->setScale({ 25,25 });
				swordUpgrade->setCollider(new AABBCollider(swordUpgrade));
				Engine::getCurrentScene()->addActor(swordUpgrade);
			}
		}

		if (m_type == "Sword")
		{
			int dropChance = rand() % 101;
			if (dropChance <= 25 || Engine::getKeyDown(KEY_P))
			{
				//Declares the Power ups Varibles and Adds the POwer up to Current Scene
				Actor* swordUpgrade = new Actor(getTransform()->getLocalPosition().x, getTransform()->getLocalPosition().y, "BigSword");
				swordUpgrade->addComponent(new SpriteComponent("Images/Powerup.png"));
				swordUpgrade->getTransform()->setScale({ 25,25 });
				swordUpgrade->setCollider(new AABBCollider(swordUpgrade));
				Engine::getCurrentScene()->addActor(swordUpgrade);
			}
		}

		//Decrement the Enemy Count and delete the enemy
		m_spawner->setNumberOfEnemies(m_spawner->getNumberOfEnemies()-1);
		Engine::destroy(this);
	}
}

void Enemy::draw()
{
	//Draws the Colliders if Tab is pressed
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();
}
