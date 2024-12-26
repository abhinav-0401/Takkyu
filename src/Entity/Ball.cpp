#include <memory>

#include "Ball.hpp"

Ball::Ball(float radius)
    : m_shape(radius, 50), m_velocity(sf::Vector2f(0.0f, 0.0f))
{}

sf::Shape& Ball::GetShape() { return m_shape; }

sf::Vector2f Ball::GetVelocity() { return m_velocity; }

void Ball::SetVelocity(sf::Vector2f value)
{
    m_velocity = value;
}

void Ball::SetVelocity(float x, float y)
{
    m_velocity = std::move(sf::Vector2f(x, y));
}

float Ball::GetInitVelocity() { return m_initVelocity; }