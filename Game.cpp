// Game.cpp
#include "Game.h"

Game::Game(std::string character) : window(sf::VideoMode(800, 600), "Castle Camden - Platformer"), selectedCharacter(character), player(character) {
    std::cout << "Starting game with character: " << selectedCharacter << std::endl;
    enemies.emplace_back(600, 500); // Example enemy spawn
}

void Game::run() {
    while (window.isOpen()) {
        handleInput();
        update();
        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    player.handleInput();
}

void Game::update() {
    player.update();
    for (auto& enemy : enemies) {
        enemy.update(player.getBounds().getPosition());
    }
}

void Game::render() {
    window.clear();
    player.render(window);
    for (auto& enemy : enemies) {
        enemy.render(window);
    }
    window.display();
}
