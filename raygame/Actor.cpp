
#include <cmath>
#include "Actor.h"
#include "raylib.h"
#include "Sprite.h"

Actor::~Actor()
{
    delete m_globalTransform;
    delete m_localTransform;
    delete m_rotation;
    delete m_translation;
    delete m_scale;
    delete[] m_children;
    delete m_sprite;
}

Actor::Actor(float x, float y, float collisionRadius, char icon = ' ', float maxSpeed = 1)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    m_icon = icon;
    setLocalPosition(MathLibrary::Vector2(x,y));
    m_velocity = MathLibrary::Vector2();
    m_collisionRadius = collisionRadius;
    m_childCount = 0;
    m_maxSpeed = maxSpeed;
}

Actor::Actor(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed = 1) : Actor(x, y, collisionRadius, ' ', maxSpeed)
{
    m_sprite = sprite;
}

Actor::Actor(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed = 1) : Actor(x, y, collisionRadius, ' ', maxSpeed)
{
    m_sprite = new Sprite(spriteFilePath);
}

MathLibrary::Vector2 Actor::getForward()
{
    return MathLibrary::Vector2(m_globalTransform->m11, m_globalTransform->m21).getNormalized();
}

void Actor::setForward(MathLibrary::Vector2 value)
{
    MathLibrary::Vector2 lookPosition = getWorldPosition() + value.getNormalized();
    lookAt(lookPosition);
}

MathLibrary::Vector2 Actor::getWorldPosition()
{
    return MathLibrary::Vector2(m_globalTransform->m13, m_globalTransform->m23);
}

void Actor::setWorldPostion(MathLibrary::Vector2 value)
{
    if (m_parent)
    {
        setLocalPosition(value + m_parent->getWorldPosition());
    }
    else
    {
        setLocalPosition(value);
    }
}

MathLibrary::Vector2 Actor::getLocalPosition()
{
    return MathLibrary::Vector2(m_localTransform->m13, m_localTransform->m23);
}

void Actor::setLocalPosition(MathLibrary::Vector2 value)
{
    *m_translation = MathLibrary::Matrix3::createTranslation(value);
}

MathLibrary::Vector2 Actor::getVelocity()
{
    return m_velocity;
}

void Actor::setVelocity(MathLibrary::Vector2 value)
{
    m_velocity = value;
}

MathLibrary::Vector2 Actor::getAcceleration()
{
	return m_acceleration;
}

void Actor::setAcceleration(MathLibrary::Vector2 value)
{
    m_acceleration = value;
}

void Actor::start()
{
    m_started = true;
}

void Actor::addChild(Actor* child)
{
    //Create a new array with a size one greater than our old array
    Actor** appendedArray = new Actor*[m_childCount + 1];
    //Copy the values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        appendedArray[i] = m_children[i];
    }

    child->m_parent = this;

    //Set the last value in the new array to be the actor we want to add
    appendedArray[m_childCount] = child;
    //Set old array to hold the values of the new array
    m_children = appendedArray;
    m_childCount++;
}

bool Actor::removeChild(int index)
{
    //Check to see if the index is outside the bounds of our array
    if (index < 0 || index >= m_childCount)
    {
        return false;
    }

    bool actorRemoved = false;

    //Create a new array with a size one less than our old array 
    Actor** newArray = new Actor * [m_childCount + 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        //If the current index is not the index that needs to be removed,
        //add the value into the old array and increment j
        if (i != index)
        {
            newArray[j] = m_children[i];
            j++;
        }
        else
        {
            actorRemoved = true;
        }
    }
    m_children[index]->m_parent = nullptr;
    //Set the old array to be the tempArray
    m_children = newArray;
    m_childCount--;
    return actorRemoved;
}

bool Actor::removeChild(Actor* child)
{
    //Check to see if the actor was null
    if (!child)
    {
        return false;
    }

    bool actorRemoved = false;
    //Create a new array with a size one less than our old array
    Actor** newArray = new Actor * [m_childCount + 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_childCount; i++)
    {
        if (child != m_children[i])
        {
            newArray[j] = m_children[i];
            j++;
        }
        else
        {
            actorRemoved = true;
        }
    }
    child->m_parent = nullptr;
    //Set the old array to the new array
    m_children = newArray;
    m_childCount--;
    //Return whether or not the removal was successful
    return actorRemoved;
}

void Actor::setScale(MathLibrary::Vector2 scale)
{
    *m_scale = MathLibrary::Matrix3::createScale(scale);
}

void Actor::scale(MathLibrary::Vector2 scale)
{
    *m_scale = *m_scale * MathLibrary::Matrix3::createScale(scale);
}

void Actor::setRotation(float radians)
{
    *m_rotation = MathLibrary::Matrix3::createRotation(radians);
}

void Actor::rotate(float radians)
{
    *m_rotation = *m_rotation * MathLibrary::Matrix3::createRotation(radians);
}

void Actor::translate(MathLibrary::Vector2 value)
{
    *m_translation = *m_translation * MathLibrary::Matrix3::createTranslation(value * 5);
}

void Actor::lookAt(MathLibrary::Vector2 position)
{
    //Find the direction that the actor should look in
    MathLibrary::Vector2 direction = (position - getWorldPosition()).getNormalized();
    
    //Use the dotproduct to find the angle the actor needs to rotate
    float dotProd = MathLibrary::Vector2::dotProduct(getForward(), direction);
    if (abs(dotProd) > 1)
        return;
    float angle = (float)acos(dotProd);

    //Find a perpindicular vector to the direction
    MathLibrary::Vector2 perp = MathLibrary::Vector2(direction.y, -direction.x);

    //Find the dot product of the perpindicular vector and the current forward
    float perpDot = MathLibrary::Vector2::dotProduct(perp, getForward());

    //If the result isn't 0, use it to change the sign of the angle to be either positive or negative
    if (perpDot != 0)
        angle *= -perpDot / abs(perpDot);

    rotate(angle);
}

bool Actor::checkCollision(Actor* other)
{
    float distance = (other->getWorldPosition() - getWorldPosition()).getMagnitude();
    return distance <= m_collisionRadius + other->m_collisionRadius;
}

void Actor::onCollision(Actor* other)
{
}

void Actor::update(float deltaTime)
{
    *m_localTransform = *m_translation * *m_rotation * *m_scale;

    updateGlobalTransform();

    setVelocity(m_velocity + m_acceleration);

    if (m_velocity.getMagnitude() > m_maxSpeed)
        m_velocity = m_velocity.getNormalized() * m_maxSpeed;

    //Increase position by the current velocity
    translate(m_velocity * deltaTime);
}

void Actor::draw()
{
    //DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, 50, BLUE);
    //Draws the actor and a line indicating it facing to the raylib window
    DrawLine(
        (int)(getWorldPosition().x * 32),
        (int)(getWorldPosition().y * 32),
        (int)((getWorldPosition().x + getForward().x) * 32),
        (int)((getWorldPosition().y + getForward().y) * 32),
        WHITE
    );

    if (m_sprite)
        m_sprite->draw(*m_globalTransform);
    //Raylib.DrawCircleLines((int)(WorldPosition.X * 32), (int)(WorldPosition.Y * 32), _collisionRadius * 32, _rayColor);
}

void Actor::debug()
{
}


void Actor::end()
{
    m_started = false;
}

void Actor::updateFacing()
{
    if (m_velocity.getMagnitude() <= 0)
        return;

    getForward() = m_velocity.getNormalized();
}

void Actor::updateGlobalTransform()
{
    if (m_parent)
        *m_globalTransform = *(m_parent->m_globalTransform) * (*m_localTransform);
    else
        *m_globalTransform = *m_localTransform;

    for (int i = 0; i < m_childCount; i++)
    {
        m_children[i]->updateGlobalTransform();
    }
}
