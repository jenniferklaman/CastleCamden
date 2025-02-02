#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

enum class MenuState { MAIN, CHARACTER_SELECT, LEVEL_SELECT };

class GameMenu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    std::vector<std::string> menuOptions = {"Start Game", "Character Select", "Exit"};
    int selectedItem = 0;
    MenuState state = MenuState::MAIN;

public:
    GameMenu();
    void run();

private:
    void handleInput();
    void navigateMenu(int direction);
    void render();
};

#endif
