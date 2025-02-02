#include "GameMenu.h"
#include <iostream>

GameMenu::GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu"), selectedItem(0), state(MenuState::MAIN) {
    // Load font
    if (!font.loadFromFile("Debrosee-ALPnL.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    // Title setup
    title.setFont(font);
    title.setString("Castle Camden");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(250.0f, 50.0f);

    // Menu options setup
    for (int i = 0; i < static_cast<int>(menuOptions.size()); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(40);
        text.setPosition(300.0f, 200.0f + (i * 50.0f));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        menuItems.push_back(text);
    }

    // Enable key repeat for smoother input
    window.setKeyRepeatEnabled(true);
}

void GameMenu::run() {
    while (window.isOpen()) {
        handleInput();
        updateState();
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
            std::cout << "Key Pressed: " << event.key.code << std::endl;

            if (event.key.code == sf::Keyboard::Up) {
                navigateMenu(-1);
            } else if (event.key.code == sf::Keyboard::Down) {
                navigateMenu(1);
            } else if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Enter Pressed! Selected: " << selectedItem << std::endl;
                selectOption();
            }
        }
    }
}

void GameMenu::navigateMenu(int direction) {
    menuItems[selectedItem].setFillColor(sf::Color::White);

    int menuSize = static_cast<int>(menuOptions.size());
    selectedItem = (selectedItem + direction + menuSize) % menuSize;

    menuItems[selectedItem].setFillColor(sf::Color::Red);
}

void GameMenu::selectOption() {
    switch (selectedItem) {
        case 0:
            std::cout << "Going to Level Selection...\n";
            state = MenuState::LEVEL_SELECT;
            break;
        case 1:
            std::cout << "Going to Character Selection...\n";
            state = MenuState::CHARACTER_SELECT;
            break;
        case 2:
            std::cout << "Exiting game...\n";
            window.close();
            break;
        default:
            break;
    }
}

void GameMenu::updateState() {
    if (state == MenuState::LEVEL_SELECT) {
        std::cout << "🚀 Transitioning to Level Selection!\n";
        state = MenuState::MAIN;
    } else if (state == MenuState::CHARACTER_SELECT) {
        std::cout << "🎭 Transitioning to Character Selection!\n";
        state = MenuState::MAIN;
    }
}

void GameMenu::render() {
    window.clear();
    window.draw(title);
    for (auto& item : menuItems) {
        window.draw(item);
    }
    window.display();
}
