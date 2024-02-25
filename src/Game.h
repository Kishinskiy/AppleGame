#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace  AppleGame
{
    struct Game
    {
        Player player;
        Apple apples[NUM_APPLES];
        Rock rocks[NUM_ROCKS];

        // Global game data
        int numEatenApples = 0;
        bool isGameFinished = false;
        float timeSinceGameFinish = 0.f;
        sf::RectangleShape background;

        //Init Textures
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        //Audio
        sf::SoundBuffer eatAppleSoundBuffer;
        sf::SoundBuffer gameOverSoundBuffer;
        sf::Sound appleEatSound;
        sf::Sound deathSound;

    };

    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinializeGame();
}

