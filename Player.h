// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    sf::RectangleShape shape;
    float speed = 5.0f;
    bool isJumping = false;
    float gravity = 0.5f;
    float velocityY = 0.0f;
    std::string characterName;

public:
    Player(std::string character);
    void handleInput();
    void update();
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    void attack(); // Placeholder for attack mechanic
};

#endif
