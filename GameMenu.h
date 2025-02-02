#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Enum to track menu state
enum class MenuState { MAIN, LEVEL_SELECT, CHARACTER_SELECT };

class GameMenu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    std::vector<std::string> menuOptions = {"Start Game", "Character Select", "Exit"};
    
    int selectedItem;  // Keeps track of which menu item is highlighted
    MenuState state;   // Tracks menu state

public:
    GameMenu();
    void run();

private:
    void handleInput();
    void navigateMenu(int direction);
    void selectOption();   // Function to handle selecting a menu option
    void updateState();    // Function to handle transitions (level selection, etc.)
    void render();
};

#endif
