#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class CharacterSelection {
private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Text> characterItems;
    std::vector<std::string> characters = {"Jen", "Eden", "Ale", "Alyssa"};
    int selectedItem = 0;

public:
    CharacterSelection();
    void run();

private:
    void handleInput();
    void navigateCharacters(int direction);
    void render();
};

#endif
