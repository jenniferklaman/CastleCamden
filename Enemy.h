// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::RectangleShape shape;
    float speed = 2.0f;

public:
    Enemy(float x, float y);
    void update(sf::Vector2f playerPosition);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

#endif