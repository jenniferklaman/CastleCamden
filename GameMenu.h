#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Enum to track menu state
enum class MenuState { MAIN, LEVEL_SELECT, CHARACTER_SELECT, HOW_TO_PLAY };

class GameMenu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    sf::Text titleShadow; // Shadow effect for the title
    sf::RectangleShape menuBackground; // Background behind menu items
    std::vector<sf::Text> menuItems;
    std::vector<std::string> menuOptions = {"Start Game", "Character Select", "How to Play", "Exit"};

    int selectedItem;  // Keeps track of which menu item is highlighted
    MenuState state;   // Tracks menu state

    // Single Background Texture and Sprite
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // How to Play Screen
    sf::Text howToPlayText;

public:
    GameMenu();
    void run();

private:
    void handleInput();
    void handleMouseInput(sf::Vector2i mousePos, bool clicked = false);
    void navigateMenu(int direction);
    void selectOption();
    void updateState();
    void render();
    void renderHowToPlay();
};

#endif
