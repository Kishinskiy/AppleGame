#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 10.f;

int main() {

    auto window = sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Apple Game"};
    window.setFramerateLimit(144);

    // set player position and speed
    float playerX = SCREEN_WIDTH / 2.f;
    float playerY = SCREEN_HEIGHT / 2.f;
    float playerSpeed = INITIAL_SPEED;

    // set player direction
    int playerDirection = 0; // 0 - right, 1 - up, 2 - left, 3 - down

    // player Shape
    sf::RectangleShape playerShape;
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setPosition(playerX, playerY);

    // Init Time
    sf::Clock gameClock;

    while (window.isOpen()) {
        // set delta time
        float deltaTime = gameClock.restart().asSeconds();

        // game close event
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // KeyBinding
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerDirection = 0;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerDirection = 1;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerDirection = 2;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerDirection = 3;
        }

        // incrase speed
        playerSpeed += ACCELERATION * deltaTime;

        //Player Movement
        switch (playerDirection) {
            case 0:
                playerX += playerSpeed * deltaTime;
                break;
            case 1:
                playerY -= playerSpeed * deltaTime;
                break;
            case 2:
                playerX -= playerSpeed * deltaTime;
                break;
            case 3:
                playerY += playerSpeed * deltaTime;
                break;
        }

        // check border collision
        if (playerX - PLAYER_SIZE / 2.f < 0.f ||
            playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
            playerY - PLAYER_SIZE / 2.f < 0.f ||
            playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) {
            // Stop Game
            window.close();
            break;
        }

        window.clear();
        playerShape.setPosition(playerX, playerY);
        window.draw(playerShape);
        window.display();
    }
}
