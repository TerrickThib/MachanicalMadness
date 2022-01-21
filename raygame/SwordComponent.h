#pragma once
#include "Component.h"
class SpriteComponent;
class AABBCollider;
class SwordComponent :
	public Component
{
public:
	SwordComponent(const char* name = "SwordComponent") : Component::Component(name) {};
	void swingSword();
	bool getInUse() { return m_inUse; }
	Actor* getSword() { return m_sword; }

	void update(float deltaTime) override;

 private:
	bool m_inUse;
	SpriteComponent* m_sprite;
	Actor* m_sword;
	float m_timer = 0;
};

