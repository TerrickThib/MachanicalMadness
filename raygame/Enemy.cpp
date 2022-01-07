#include "Enemy.h"
#include "Engine.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "SwordComponent.h"
#include "Transform2D.h"
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "raylib.h"

void Enemy::start()
{
	Actor::start();

	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_moveComponent->setMaxSpeed(10);
	if (m_type == "Rusher")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Rusher.png")));
		getTransform()->setScale({ 25,25 });
		setCollider(new CircleCollider(10, this));
	}
	
	else if (m_type == "Gunner")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Gunner.png")));
		getTransform()->setScale({ 35,70 });
		setCollider(new AABBCollider(this));
	}
	else if (m_type == "Sword")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Sword.png")));
		getTransform()->setScale({ 35,70 });
		setCollider(new AABBCollider(70,70,this));
		m_swordComponent = dynamic_cast<SwordComponent*>(addComponent(new SwordComponent()));
	}
}

void Enemy::update(float deltaTime)
{
	if (m_type == "Sword" && !m_swordComponent->getInUse() || m_type != "Sword")
	{
		Actor::update(deltaTime);

		MathLibrary::Vector2 moveDirection = (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getNormalized();
		getTransform()->setForward(moveDirection);
		m_moveComponent->setVelocity(moveDirection * 50);
	}
	
	if (m_type == "Sword" && (getTransform()->getWorldPosition() - m_target->getTransform()->getWorldPosition()).getMagnitude() < 100 && !m_swordComponent->getInUse())
	{
		m_swordComponent->swingSword();
	}

	if(m_type == "Sword")
	m_swordComponent->update(deltaTime);
}

void Enemy::onCollision(Actor* other)
{
	if (other->getName() == "Sword" && m_type != "Sword")
		Engine::destroy(this);
	else if (other->getName() == "Sword" && m_swordComponent->getSword() != other)
		Engine::destroy(this);
}

void Enemy::draw()
{
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();
}
