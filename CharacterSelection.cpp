#include "CharacterSelection.h"

CharacterSelection::CharacterSelection() : window(sf::VideoMode(800, 600), "Character Selection") {
    if (!font.loadFromFile("retro_font.ttf")) {
        std::cerr << "Error loading font!\n";
    }

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

void CharacterSelection::run() {
    while (window.isOpen()) {
        handleInput();
        render();
    }
}

void CharacterSelection::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                navigateCharacters(-1);
            }
            if (event.key.code == sf::Keyboard::Down) {
                navigateCharacters(1);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Character Selected: " << characters[selectedItem] << std::endl;
                window.close();
            }
        }
    }
}

void CharacterSelection::navigateCharacters(int direction) {
    characterItems[selectedItem].setFillColor(sf::Color::White);
    selectedItem = (selectedItem + direction + characters.size()) % characters.size();
    characterItems[selectedItem].setFillColor(sf::Color::Red);
}

void CharacterSelection::render() {
    window.clear();
    for (auto& item : characterItems) {
        window.draw(item);
    }
    window.display();
}
