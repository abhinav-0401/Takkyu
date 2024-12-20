#include "Paddle.hpp"

Paddle::Paddle(float width, float height)
    : m_shape(sf::Vector2f(width, height))
{}

sf::Shape& Paddle::GetShape() { return m_shape; }
