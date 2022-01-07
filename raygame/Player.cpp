#include "Player.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "Transform2D.h"
#include "CircleCollider.h"
#include "SwordComponent.h"

void Player::start()
{
	Actor::start();

	m_inputComponent = dynamic_cast<InputComponent*>(addComponent(new InputComponent()));
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_moveComponent->setMaxSpeed(200);
	m_swordComponent = dynamic_cast<SwordComponent*>(addComponent(new SwordComponent()));
	m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/Robi.png")));

	getTransform()->setScale({ 35,70 });
	setCollider(new CircleCollider(15,this));
	//Set spawn point
	//Set position clamps
	m_moveComponent->setSpeed(200);

}

void Player::update(float deltaTime)
{
	if (!m_swordComponent->getInUse())
	{
		Actor::update(deltaTime);

		MathLibrary::Vector2 moveDirection = m_inputComponent->getMoveAxis();

	//Multiplys the movedirection with current speed to get Velocity
	m_moveComponent->setVelocity(moveDirection * m_moveComponent->getSpeed());

	//Caps the max speed the Actor can move
	if (m_moveComponent->getVelocity().getMagnitude() >= m_moveComponent->getMaxSpeed())
	{
		m_moveComponent->setVelocity(moveDirection * m_moveComponent->getMaxSpeed());
	}

 		if (m_inputComponent->actionInput())
			m_swordComponent->swingSword();
	}
	
	m_swordComponent->update(deltaTime);
	getCollider()->update();
}

void Player::onCollision(Actor* other)
{
	if (other->getName() == "Goal")
		Engine::CloseApplication();
	if(other->getName() == "Enemy")
		Engine::CloseApplication();
	if (other->getName() == "Sword")
	{
		Engine::CloseApplication();
	}
}

void Player::draw()
{
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();	
}
