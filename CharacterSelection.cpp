#include "CharacterSelection.h"
#include <iostream>

CharacterSelection::CharacterSelection() : window(sf::VideoMode(800, 600), "Character Selection") {
    if (!font.loadFromFile("assets/PixelTimesBold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    // Load Background Texture
    if (!backgroundTexture.loadFromFile("assets/AskrBookVIICastle.png")) {  
        std::cerr << "Error loading background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.0f, 1.0f);

    for (size_t i = 0; i < characters.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(characters[i]);
        text.setCharacterSize(40);
        text.setPosition(300, 200 + (i * 50));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        characterItems.push_back(text);
    }
}

void CharacterSelection::render() {
    window.clear();
    window.draw(backgroundSprite);  // Draw Background
    for (auto& item : characterItems) {
        window.draw(item);
    }
    window.display();
}
