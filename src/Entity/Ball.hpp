#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Ball : public Entity
{
public:
    Ball(float radius);
    sf::Vector2f GetVelocity();
    void SetVelocity(sf::Vector2f value);
    void SetVelocity(float x, float y);
    float GetInitVelocity();

    virtual sf::Shape& GetShape() override;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
    float m_initVelocity = 2.0f;
};