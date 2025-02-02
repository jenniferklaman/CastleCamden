// Player.cpp
#include "Player.h"

Player::Player(std::string character) : characterName(character) {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(100, 500);  // Starting position
}

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shape.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shape.move(speed, 0);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && !isJumping) {
        velocityY = -10.0f;  // Jump strength
        isJumping = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { 
        attack();
    }
}

void Player::update() {
    velocityY += gravity;
    shape.move(0, velocityY);

    if (shape.getPosition().y >= 500) {  
        shape.setPosition(shape.getPosition().x, 500);
        isJumping = false;
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void Player::attack() {
    std::cout << characterName << " attacked!\n";
}
