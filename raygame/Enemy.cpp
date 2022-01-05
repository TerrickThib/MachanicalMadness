#include "Enemy.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
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
		getTransform()->setScale({ 70,35 });
		setCollider(new AABBCollider(35, 12.5f, this));
	}
	else if (m_type == "Sword")
	{
		m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/MDU-Sword.png")));
		getTransform()->setScale({ 70,35 });
		setCollider(new AABBCollider(35, 12.5f, this));
	}
}

void Enemy::update(float deltaTime)
{
	Actor::update(deltaTime);

	MathLibrary::Vector2 moveDirection = (m_target->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getNormalized();
	getTransform()->setForward(moveDirection);
	m_moveComponent->setVelocity(moveDirection * 50);
}

void Enemy::onCollision(Actor* other)
{
}

void Enemy::draw()
{
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();
}
