#include "MoveComponent.h"
#include "Actor.h"
#include "Transform2D.h"

void MoveComponent::update(float deltaTime)
{
	//Add the new velocity to the old position to get the new position
	MathLibrary::Vector2 newPosition = getOwner()->getTransform()->getLocalPosition() + getVelocity() * deltaTime;

	//Allowes the players sprite to change based on movement
	MathLibrary::Vector2 forwardDirection = getVelocity().getNormalized();
	if (forwardDirection.getMagnitude())
		getOwner()->getTransform()->setForward(getVelocity().getNormalized());

	//Set the actors position to be the new position found
	getOwner()->getTransform()->setLocalPosition(newPosition);
}