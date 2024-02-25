#include "Game.h"
#include <cassert>
#include <iostream>

namespace AppleGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game);

        // Init apples
        for (auto & apple : game.apples)
        {
            InitApple(apple, game);
            assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
        }

        // Init rocks
        for (auto & rock : game.rocks)
        {
            InitRock(rock, game);
            assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
        }

        game.numEatenApples = 0;
        game.isGameFinished = false;
        game.timeSinceGameFinish = 0;
    }

    void InitGame(Game& game)
    {

        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));


        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setFillColor(sf::Color::Black);
        game.background.setPosition(0.f, 0.f);

        RestartGame(game);
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        // Update game state
        if (!game.isGameFinished)
        {
            // Handle input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.player.direction = PlayerDirection::Right;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                game.player.direction = PlayerDirection::Up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                game.player.direction = PlayerDirection::Left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                game.player.direction = PlayerDirection::Down;
            }

            // Update player state
            switch (game.player.direction)
            {
                case PlayerDirection::Right:
                {
                    game.player.position.x += game.player.speed * deltaTime;
                    break;
                }
                case PlayerDirection::Up:
                {
                    game.player.position.y -= game.player.speed * deltaTime;
                    break;
                }
                case PlayerDirection::Left:
                {
                    game.player.position.x -= game.player.speed * deltaTime;
                    break;
                }
                case PlayerDirection::Down:
                {
                    game.player.position.y += game.player.speed * deltaTime;
                    break;
                }
            }

            // Find player collisions with apples
            for (auto & apple : game.apples)
            {
                if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
                                     apple.position, APPLE_SIZE / 2.f))
                {
                    apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
                    ++game.numEatenApples;
                    game.player.speed += ACCELERATION;
                }
            }

            // Find player collisions with rocks
            for (auto & rock : game.rocks)
            {
                if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
                                        rock.position, { ROCK_SIZE, ROCK_SIZE }))
                {
                    game.isGameFinished = true;
                    game.timeSinceGameFinish = 0.f;
                }
            }

            // Check screen borders collision
            if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
            {
                game.isGameFinished = true;
                game.timeSinceGameFinish = 0.f;
            }
        }
        else
        {
            if (game.timeSinceGameFinish <= PAUSE_LENGTH)
            {
                game.timeSinceGameFinish += deltaTime;
                game.background.setFillColor(sf::Color::Red);
            }
            else
            {
                // Reset backgound
                game.background.setFillColor(sf::Color::Black);
                RestartGame(game);
            }
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background);
        DrawPlayer(game.player, window);
        for (auto & apple : game.apples)
        {
            apple.sprite.setPosition(apple.position.x, apple.position.y);
            window.draw(apple.sprite);
        }

        for (auto & rock : game.rocks)
        {
            rock.sprite.setPosition(rock.position.x, rock.position.y);
            window.draw(rock.sprite);
        }

    }

    void DeinializeGame()
    {

    }

}

