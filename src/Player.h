#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace AppleGame
{
    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
    };

    struct Game;
    void InitPlayer(Player& player, const Game& game);
    void DrawPlayer(Player& player, sf::RenderWindow& window);
}

