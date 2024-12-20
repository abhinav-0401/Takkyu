#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Ball : public Entity
{
public:
    Ball(float radius);

    virtual sf::Shape& GetShape() override;

private:
    sf::CircleShape m_shape;
};