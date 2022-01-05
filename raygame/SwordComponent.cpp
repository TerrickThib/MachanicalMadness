#include "SwordComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AABBCollider.h"
#include "Engine.h"

void SwordComponent::swingSword()
{
	m_inUse = true;
	m_sword = new Actor(getOwner()->getTransform()->getLocalPosition().x + (getOwner()->getTransform()->getForward().x * 50), getOwner()->getTransform()->getLocalPosition().y + (getOwner()->getTransform()->getForward().y *50), "Sword");
	m_sprite = dynamic_cast <SpriteComponent*>(m_sword->addComponent(new SpriteComponent("Images/Sword.png")));
	m_sword->getTransform()->setScale({ 50, 20 });
	m_collider = new AABBCollider(60,30,m_sword);
	m_sword->setCollider(m_collider);
	Engine::getCurrentScene()->addActor(m_sword);
}

void SwordComponent::start()
{
}

void SwordComponent::update(float deltaTime)
{
	if (m_inUse)
		m_timer += deltaTime;

	if (m_timer <= 1)
	{
		m_inUse = false;
		m_timer = 0;
		m_sprite = nullptr;
		m_sword = nullptr;
	}
}

void SwordComponent::draw()
{
}

void SwordComponent::end()
{
}

void SwordComponent::onCollision(Actor* other)
{

}
