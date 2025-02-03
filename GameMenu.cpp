#include "GameMenu.h"
#include <iostream>

GameMenu::GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu"), selectedItem(0), state(MenuState::MAIN) {
    // Load font
    if (!font.loadFromFile("assets/PixelTimesBold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    // Load Background Texture (New Image)
    if (!backgroundTexture.loadFromFile("assets/AskrBookVIICastle.png")) {  
        std::cerr << "Error loading background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.0f, 1.0f);

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
        text.setPosition(350.0f, 200.0f + (i * 50.0f));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        menuItems.push_back(text);
    }

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

        if (state == MenuState::MAIN) {
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                handleMouseInput(mousePos);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                handleMouseInput(mousePos, true);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    navigateMenu(-1);
                } else if (event.key.code == sf::Keyboard::Down) {
                    navigateMenu(1);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    selectOption();
                }
            }
        }
        else if (state == MenuState::HOW_TO_PLAY && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            state = MenuState::MAIN;
        }
    }
}

void GameMenu::handleMouseInput(sf::Vector2i mousePos, bool clicked) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::FloatRect bounds = menuItems[i].getGlobalBounds();

        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            menuItems[selectedItem].setFillColor(sf::Color::White);
            selectedItem = static_cast<int>(i);
            menuItems[selectedItem].setFillColor(sf::Color::Red);

            if (clicked) {
                selectOption();
            }
            break;
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
            std::cout << "Opening How to Play...\n";
            state = MenuState::HOW_TO_PLAY;
            break;
        case 3:
            std::cout << "Exiting game...\n";
            window.close();
            break;
    }
}

void GameMenu::updateState() {
    if (state == MenuState::LEVEL_SELECT) {
        std::cout << "🚀 Transitioning to Level Selection!\n";
        state = MenuState::MAIN; // Placeholder: Implement level selection logic
    } 
    else if (state == MenuState::CHARACTER_SELECT) {
        std::cout << "🎭 Transitioning to Character Selection!\n";
        state = MenuState::MAIN; // Placeholder: Implement character selection logic
    } 
    else if (state == MenuState::HOW_TO_PLAY) {
        std::cout << "📖 Showing How to Play screen!\n";
    }
}


void GameMenu::render() {
    window.clear();
    window.draw(backgroundSprite);  // Draw Background
    window.draw(title);
    for (auto& item : menuItems) {
        window.draw(item);
    }
    window.display();
}

void GameMenu::renderHowToPlay() {
    window.clear();
    window.draw(howToPlayText);
    window.display();
}
