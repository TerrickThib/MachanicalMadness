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

	void start() override;
	void update(float deltaTime) override;
	void draw() override;
	void end() override;
	void onCollision(Actor* other) override;

 private:
	bool m_inUse;
	SpriteComponent* m_sprite;
	Actor* m_sword;
	AABBCollider* m_collider;
	float m_timer;
};

