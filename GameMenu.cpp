#include "GameMenu.h"
#include <iostream>

GameMenu::GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu"), selectedItem(0), state(MenuState::MAIN) {
    // Load font
    if (!font.loadFromFile("assets/PixelTimesBold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    // Load Single Background Texture
    if (!backgroundTexture.loadFromFile("assets/menuBackground.png")) {  
        std::cerr << "Error loading background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Get window size
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Scale the background to fit the screen
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setPosition(0, 0);

    // Title setup (shifted left)
    title.setFont(font);
    title.setString("Castle Camden");
    title.setCharacterSize(55);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(50.0f, 20.0f); // **Shifted left**

    titleShadow.setFont(font);
    titleShadow.setString("Castle Camden");
    titleShadow.setCharacterSize(55);
    titleShadow.setFillColor(sf::Color(0, 0, 0, 180)); // Shadow opacity for contrast
    titleShadow.setPosition(53.0f, 23.0f); // Slight offset for shadow effect

    // Calculate total height of the menu items
    float totalMenuHeight = (menuOptions.size() * 30) + ((menuOptions.size() - 1) * 45);  // 36px text size + 45px spacing

    // Adjust background box size to fit all text
    menuBackground.setSize(sf::Vector2f(350.0f, totalMenuHeight + 50));  // Extra padding around text
    menuBackground.setFillColor(sf::Color(0, 0, 0, 220));  // Darker for contrast

    // Center the menu vertically by adjusting the starting Y position
    float menuStartY = (window.getSize().y - totalMenuHeight) / 2;
    float menuStartX = 320.0f; // Align menu text

    // Reduced Menu Text Size to Fit Inside Box
    for (int i = 0; i < static_cast<int>(menuOptions.size()); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(30);  // **Reduced from 42 → 36px**
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        text.setPosition(menuStartX, menuStartY + (i * 45)); // Adjusted Y position for centering
        menuItems.push_back(text);
    }

    // Set position for menu background box
    menuBackground.setPosition(menuStartX - 20.0f, menuStartY - 20.0f);  // Adjusted position

    // Set up How to Play screen text
    howToPlayText.setFont(font);
    howToPlayText.setString("HOW TO PLAY:\n- Use UP/DOWN arrows or mouse to navigate.\n- Press ENTER or click to select.\n- Enjoy the game!\n\nPress ESC to go back.");
    howToPlayText.setCharacterSize(30);
    howToPlayText.setFillColor(sf::Color::White);
    howToPlayText.setPosition(100.0f, 200.0f);

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

        // Allow users to exit "How to Play"
        if (state == MenuState::HOW_TO_PLAY) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                state = MenuState::MAIN; // Return to main menu
            }
            return; // Prevent other inputs from affecting the menu
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
        state = MenuState::MAIN;
    } 
    else if (state == MenuState::CHARACTER_SELECT) {
        std::cout << "🎭 Transitioning to Character Selection!\n";
        state = MenuState::MAIN;
    } 
    else if (state == MenuState::HOW_TO_PLAY) {
        std::cout << "📖 Showing How to Play screen!\n";
    }
}

void GameMenu::render() {
    window.clear();
    
    // Draw Single Background
    window.draw(backgroundSprite);

    if (state == MenuState::HOW_TO_PLAY) {
        renderHowToPlay();
    } else {
        window.draw(titleShadow); // Shadow for better contrast
        window.draw(title);
        window.draw(menuBackground); // Dark rectangle behind menu
        for (auto& item : menuItems) {
            window.draw(item);
        }
    }

    window.display();
}

void GameMenu::renderHowToPlay() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(howToPlayText);
    window.display();
}
