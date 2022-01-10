#include "Player.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "Transform2D.h"
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "SwordComponent.h"
#include "raymath.h"
#include "UIText.h"
#include "Scene.h"

void Player::start()
{
	Actor::start();

	m_inputComponent = dynamic_cast<InputComponent*>(addComponent(new InputComponent()));
	m_moveComponent = dynamic_cast<MoveComponent*>(addComponent(new MoveComponent()));
	m_moveComponent->setMaxSpeed(1000);
	m_swordComponent = dynamic_cast<SwordComponent*>(addComponent(new SwordComponent()));
	m_spriteComponent = dynamic_cast <SpriteComponent*>(addComponent(new SpriteComponent("Images/Robi.png")));

	getTransform()->setScale({ 35,70 });
	setCollider(new CircleCollider(15,this));
	//Set spawn point
	//Set position clamps
	m_moveComponent->setSpeed(100);

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

	//Clamps your position between two points and then sets your LOcal position to be resultX and resultY
	float resultX = Clamp(getTransform()->getLocalPosition().x, 23, 685);
	float resultY = Clamp(getTransform()->getLocalPosition().y, 23, 785);
	getTransform()->setLocalPosition(MathLibrary::Vector2(resultX,resultY));

	
	m_swordComponent->update(deltaTime);

	if (m_hasPowerUp)
	{
		//Check how long they have been powered up for
		m_powerUpTimer += deltaTime;
		m_swordComponent->getSword()->getTransform()->setScale({ 45,75 });
		m_swordComponent->getSword()->setCollider(new AABBCollider(75,75,m_swordComponent->getSword()));
		if (m_powerUpTimer >= 20)
		{
			resetPowerUp();
		}
	}

	getCollider()->update();
}

void Player::onCollision(Actor* other)
{
	if (other->getName() == "Goal")
	{
		Scene* endScene = new Scene();
		Engine::addScene(endScene);
		Engine::setCurrentScene(2);
		UIText* win = new UIText(200, 350, "Test", BLUE, 340, 100, 40, "  TEST OVER Result: SUCCESS");
		Engine::getCurrentScene()->addUIElement(win);
	}

	if (other->getName() == "Enemy" || other->getName() == "EnemySword")
	{
		Scene* endScene = new Scene();
		Engine::addScene(endScene);
		Engine::setCurrentScene(1);
		UIText* lose = new UIText(225, 350, "Test", RED, 300, 100, 40, "  TEST OVER Result: FAILURE");
		Engine::getCurrentScene()->addUIElement(lose);
		if (Engine::getKeyPressed(KEY_ENTER))
		{
			Engine::setCurrentScene(0);
		}
	}
		
}

void Player::draw()
{
	Actor::draw();
	if (IsKeyDown(KEY_TAB))
		getCollider()->draw();	
}

void Player::resetPowerUp()
{
	m_hasPowerUp = false;
	m_powerUpTimer = 0;
}
