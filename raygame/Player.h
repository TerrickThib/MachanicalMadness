#pragma once
#include "Actor.h"
class InputComponent;
class MoveComponent;
class SpriteComponent;
class SwordComponent;

class Player :
	public Actor
{
public:
	Player(float x, float y, const char* name) : Actor(x, y, name) {}
	SwordComponent* getSwordComponent() { return m_swordComponent; }
	void start() override;
	void update(float deltaTime) override;
	void onCollision(Actor* other) override;
	void draw() override;

private:
	InputComponent* m_inputComponent;
	MoveComponent* m_moveComponent;
	SpriteComponent* m_spriteComponent;
	SwordComponent* m_swordComponent;
};

