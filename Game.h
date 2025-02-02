// Game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy> enemies;
    std::string selectedCharacter; // Stores the chosen character

public:
    Game(std::string character);
    void run();
    void handleInput();
    void update();
    void render();
};

#endif