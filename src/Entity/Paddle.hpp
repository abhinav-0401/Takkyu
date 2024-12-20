#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Paddle : public Entity
{
public:
    Paddle(float width, float height);

    virtual sf::Shape& GetShape() override;

private:
    sf::RectangleShape m_shape;
};