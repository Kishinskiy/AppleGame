#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"


namespace AppleGame
{
    struct Rock
    {
        Position2D position;
        sf::Sprite sprite;
    };

    struct Game;
    void InitRock(Rock& rock, const Game& game);
}

