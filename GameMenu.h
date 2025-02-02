#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <iostream>

// Abstract base class for menus
class Menu {
public:
    virtual void handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Menu() = default;
};

// Main menu class
class MainMenu : public Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    std::vector<std::string> menuOptions = {"Start Game", "How to Play", "Exit"};
    int selectedItem = 0;

public:
    MainMenu();
    void handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) override;
    void render(sf::RenderWindow& window) override;
};

// Start Game submenu
class StartGameMenu : public Menu {
private:
    sf::Font font;
    std::vector<sf::Text> startGameItems;
    std::vector<std::string> startGameOptions = {"New Game", "Load Game", "Back"};
    int selectedItem = 0;

public:
    StartGameMenu();
    void handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) override;
    void render(sf::RenderWindow& window) override;
};

// How to Play screen
class HowToPlayMenu : public Menu {
private:
    sf::Font font;
    sf::Text instructions;
    sf::Text backText;

public:
    HowToPlayMenu();
    void handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) override;
    void render(sf::RenderWindow& window) override;
};

// GameMenu class that controls the menu system
class GameMenu {
private:
    sf::RenderWindow window;
    std::stack<std::unique_ptr<Menu>> menuStack;

public:
    GameMenu();
    void run();
};

#endif
