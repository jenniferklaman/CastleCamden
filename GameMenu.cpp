#include "GameMenu.h"

GameMenu::GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu") {
    if (!font.loadFromFile("Debrosee-ALPnL.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    title.setFont(font);
    title.setString("Castle Camden");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(250, 50);

    for (size_t i = 0; i < menuOptions.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(40);
        text.setPosition(300, 200 + (i * 50));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        menuItems.push_back(text);
    }
}

void GameMenu::run() {
    while (window.isOpen()) {
        handleInput();
        render();
    }
}

void GameMenu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                navigateMenu(-1);
            }
            if (event.key.code == sf::Keyboard::Down) {
                navigateMenu(1);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (selectedItem == 0) {
                    state = MenuState::LEVEL_SELECT;
                } else if (selectedItem == 1) {
                    state = MenuState::CHARACTER_SELECT;
                } else if (selectedItem == 2) {
                    window.close();
                }
            }
        }
    }
}

void GameMenu::navigateMenu(int direction) {
    menuItems[selectedItem].setFillColor(sf::Color::White);
    selectedItem = (selectedItem + direction + menuOptions.size()) % menuOptions.size();
    menuItems[selectedItem].setFillColor(sf::Color::Red);
}

void GameMenu::render() {
    window.clear();
    window.draw(title);
    for (auto& item : menuItems) {
        window.draw(item);
    }
    window.display();
}
