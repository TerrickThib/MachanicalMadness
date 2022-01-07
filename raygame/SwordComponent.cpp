#include "SwordComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "Engine.h"
#include <iostream>
#include <raylib.h>

void SwordComponent::swingSword()
{
	m_inUse = true;
	m_sword = new Actor(getOwner()->getTransform()->getLocalPosition().x + (getOwner()->getTransform()->getForward().x * 50), getOwner()->getTransform()->getLocalPosition().y + (getOwner()->getTransform()->getForward().y *50), "Sword");
	m_sprite = dynamic_cast <SpriteComponent*>(m_sword->addComponent(new SpriteComponent("Images/Sword.png")));
	m_sword->getTransform()->setScale({ 30, 50 });
	m_sword->getTransform()->setForward({ getOwner()->getTransform()->getLocalPosition().x + getOwner()->getTransform()->getForward().x * 10000, getOwner()->getTransform()->getLocalPosition().y + getOwner()->getTransform()->getForward().y * 10000 });
	if (getOwner()->getName() == "Player")
	{
		m_sword->setCollider(new AABBCollider(50, 50, m_sword));
	}
	else if (getOwner()->getName() == "Enemy")
	{
		m_sword->setCollider(new CircleCollider(25, m_sword));
	}
	Engine::getCurrentScene()->addActor(m_sword);
}

void SwordComponent::start()
{
}

void SwordComponent::update(float deltaTime)
{
	if (m_inUse)
	{
		m_timer += deltaTime;
		m_sword->getTransform()->rotate(-deltaTime * 6.3f);
	}
		

	if (m_timer >= 0.5f)
	{
		m_inUse = false;
		m_timer = 0;
		Engine::getCurrentScene()->removeActor(m_sword);
	}
}

void SwordComponent::draw()
{
}

void SwordComponent::end()
{
	Engine::getCurrentScene()->removeActor(m_sword);
}

void SwordComponent::onCollision(Actor* other)
{

}
