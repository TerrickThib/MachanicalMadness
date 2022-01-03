#pragma once

#include <Vector2.h>
#include <Matrix3.h>

class Sprite;

class Actor
{
public:
    Actor() {}
    ~Actor();
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Actor(float x, float y, float collisionRadius, char icon, float maxSpeed);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Actor(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Actor(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);

    bool getStarted() { return m_started; }
    Actor* getParent() { return m_parent; }

    MathLibrary::Vector2 getForward();
    void setForward(MathLibrary::Vector2 value);

    MathLibrary::Vector2 getWorldPosition();
    void setWorldPostion(MathLibrary::Vector2 value);
    MathLibrary::Vector2 getLocalPosition();
    void setLocalPosition(MathLibrary::Vector2 value);

    MathLibrary::Vector2 getVelocity();
    void setVelocity(MathLibrary::Vector2 value);
    MathLibrary::Vector2 getAcceleration();
    void setAcceleration(MathLibrary::Vector2 value);

    virtual void start();

    void addChild(Actor* child);
    bool removeChild(int index);
    bool removeChild(Actor* child);
    int getChildCount() { return m_childCount; }
    Actor** getChildren() { return m_children; }

    void setScale(MathLibrary::Vector2 scale);
    void scale(MathLibrary::Vector2 scale);

    /// <summary>
    /// Set the rotation angle to be the given value in radians
    /// </summary>
    /// <param name="radians">The angle to se the transform's rotation to</param>
    void setRotation(float radians);

    /// <summary>
    /// Increases the angle of rotation by the given amount.
    /// </summary>
    /// <param name="radians">The amount of radians to increase the rotation by</param>
    void rotate(float radians);

    void translate(MathLibrary::Vector2 value);

    /// <summary>
    /// Rotates the actor to face the given position
    /// </summary>
    /// <param name="position">The position the actor should be facing</param>
    void lookAt(MathLibrary::Vector2 position);

    bool checkCollision(Actor* other);
    virtual void onCollision(Actor* other);

    virtual void update(float deltaTime);
    virtual void draw();
    virtual void debug();
    virtual void end();

protected:
    /// <summary>
    /// Updates the actors forward vector to be
    /// the last direction it moved in
    /// </summary>
    void updateFacing();

private:
    /// <summary>
    /// Updates the global transform to be the combination of the paernt and local
    /// transforms. Updates the transforms for all children of this actor
    /// </summary>
    void updateGlobalTransform();

protected:
    MathLibrary::Matrix3* m_globalTransform;
    MathLibrary::Matrix3* m_localTransform;
    MathLibrary::Matrix3* m_rotation;
    MathLibrary::Matrix3* m_translation;
    MathLibrary::Matrix3* m_scale;
    Actor** m_children;
    MathLibrary::Vector2 m_velocity;
    MathLibrary::Vector2 m_acceleration;
    float m_maxSpeed;
    char m_icon;

private:
    bool m_started;
    float m_collisionRadius;
    Actor* m_parent;
    int m_childCount;
    Sprite* m_sprite;
};

