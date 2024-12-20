#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
    virtual sf::Shape& GetShape() = 0;
};