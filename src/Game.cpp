#include "Game.h"
#include <cassert>

namespace AppleGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game);

        // Init apples
        for (auto & apple : game.apples)
        {
            InitApple(apple, game);

        }

        // Init rocks
        for (auto & rock : game.rocks)
        {
            InitRock(rock, game);

        }

        game.numEatenApples = 0;
        game.isGameFinished = false;
        game.timeSinceGameFinish = 0;
    }

    void InitGame(Game& game)
    {
        //loat Textures
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));
        //Load Sounds
        assert(game.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
        assert(game.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "/Death.wav"));


        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setFillColor(sf::Color::Black);
        game.background.setPosition(0.f, 0.f);

        game.appleEatSound.setBuffer(game.eatAppleSoundBuffer);
        game.deathSound.setBuffer(game.gameOverSoundBuffer);

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
                    game.appleEatSound.play();
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
                    game.deathSound.play();
                }
            }

            // Check screen borders collision
            if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
            {
                game.isGameFinished = true;
                game.timeSinceGameFinish = 0.f;
                game.deathSound.play();
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
            DrawApple(apple, window);
        }

        for (auto & rock : game.rocks)
        {
            DrawRock(rock, window);
        }

    }

    void DeinializeGame()
    {

    }

}

