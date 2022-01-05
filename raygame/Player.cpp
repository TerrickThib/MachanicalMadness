#include "Player.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "Transform2D.h"
#include "AABBCollider.h"

void Player::start()
{
	Actor::start();

	m_inputComponent = dynamic_cast<InputComponent*>(addComponent(new InputComponent()));
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_moveComponent->setMaxSpeed(10);
	m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/Robi.png")));
	m_moveComponent->setSpeed(2);
	m_moveComponent->setCurrentSpeed(1);

	getTransform()->setScale({ 35,70 });
	setCollider(new AABBCollider(this));
	//Set spawn point
	//Set Move speed
	//Set position clamps
}

void Player::update(float deltaTime)
{
	Actor::update(deltaTime);

	MathLibrary::Vector2 moveDirection = m_inputComponent->getMoveAxis();

	//Multiplys the movedirection with current speed to get Velocity
	m_moveComponent->setVelocity(moveDirection * m_moveComponent->getCurrentSpeed());

	while (m_moveComponent->getVelocity().getMagnitude() <= m_moveComponent->getMaxSpeed())
	{
		m_moveComponent->setCurrentSpeed( m_moveComponent->getCurrentSpeed() + m_moveComponent->getSpeed());
		return;
	}

	if (m_moveComponent->getVelocity().getMagnitude() >= m_moveComponent->getMaxSpeed())
	{
		m_moveComponent->setVelocity(moveDirection * m_moveComponent->getMaxSpeed());
	}

}

void Player::onCollision(Actor* other)
{
	if (other->getName() == "Goal")
		Engine::CloseApplication();
	if(other->getName() == "Enemy")
		Engine::CloseApplication();
}

void Player::draw()
{
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();	
}
