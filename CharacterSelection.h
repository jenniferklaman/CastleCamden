// CharacterSelection.h
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
    std::vector<std::string> characters = {"Eden", "Alyssa", "Ale", "Jen"};
    int selectedItem = 0;
    std::string selectedCharacter;

public:
    CharacterSelection();
    std::string run(); // Returns the chosen character

private:
    void handleInput();
    void navigateCharacters(int direction);
    void render();
};

#endif