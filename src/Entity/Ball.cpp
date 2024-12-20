#include "Ball.hpp"

Ball::Ball(float radius)
    : m_shape(radius, 50)
{}

sf::Shape& Ball::GetShape() { return m_shape; }