// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(float x, float y) {
    shape.setSize(sf::Vector2f(40, 40));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Enemy::update(sf::Vector2f playerPosition) {
    if (shape.getPosition().x > playerPosition.x) {
        shape.move(-speed, 0);
    } else {
        shape.move(speed, 0);
    }
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(shape);
}
