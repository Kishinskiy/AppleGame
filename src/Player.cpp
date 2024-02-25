#include "Player.h"
#include "Game.h"

namespace  AppleGame
{
    void InitPlayer(Player& player, const Game& game)
    {
        // Init player state
        player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.speed = INITIAL_SPEED;
        player.direction = PlayerDirection::Right;

        // Init player shape
        player.sprite.setTexture(game.playerTexture);
        SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);

        if (player.direction == PlayerDirection::Left)
        {
            SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation(0.f);
        } else
        {
            SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
            player.sprite.setRotation((float)player.direction * -90.f);
        }
    }
}

