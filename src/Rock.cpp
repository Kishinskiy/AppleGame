#include "Rock.h"
#include "Game.h"

namespace AppleGame
{
    void InitRock(Rock& rock, const Game& game)
    {
        rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

        // Init player shape
        rock.sprite.setTexture(game.rockTexture);
        SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
        SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
    }
}

