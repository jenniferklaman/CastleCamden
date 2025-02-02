#include "GameMenu.h"
#include "CharacterSelection.h"
#include "Game.h"

// ---------------- MAIN MENU ----------------
MainMenu::MainMenu() {
    if (!font.loadFromFile("Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    title.setFont(font);
    title.setString("Castle Camden");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(250.0f, 50.0f);

    for (size_t i = 0; i < menuOptions.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuOptions[i]);
        text.setCharacterSize(40);
        text.setPosition(300.0f, 200.0f + (i * 50.0f));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        menuItems.push_back(text);
    }
}

void MainMenu::handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                menuItems[selectedItem].setFillColor(sf::Color::White);
                selectedItem = (selectedItem - 1 + menuOptions.size()) % menuOptions.size();
                menuItems[selectedItem].setFillColor(sf::Color::Red);
            } 
            else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                menuItems[selectedItem].setFillColor(sf::Color::White);
                selectedItem = (selectedItem + 1) % menuOptions.size();
                menuItems[selectedItem].setFillColor(sf::Color::Red);
            } 
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedItem == 0) {
                    menuStack.push(std::make_unique<StartGameMenu>());
                } 
                else if (selectedItem == 1) {
                    menuStack.push(std::make_unique<HowToPlayMenu>());
                } 
                else if (selectedItem == 2) {
                    window.close();
                }
            }
        }
    }
}

void MainMenu::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(title);
    for (auto& item : menuItems) {
        window.draw(item);
    }
    window.display();
}

// ---------------- START GAME MENU ----------------
StartGameMenu::StartGameMenu() {
    if (!font.loadFromFile("Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    for (size_t i = 0; i < startGameOptions.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(startGameOptions[i]);
        text.setCharacterSize(40);
        text.setPosition(320.0f, 250.0f + (i * 50.0f));
        text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
        startGameItems.push_back(text);
    }
}

void StartGameMenu::handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                startGameItems[selectedItem].setFillColor(sf::Color::White);
                selectedItem = (selectedItem - 1 + startGameOptions.size()) % startGameOptions.size();
                startGameItems[selectedItem].setFillColor(sf::Color::Red);
            } 
            else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                startGameItems[selectedItem].setFillColor(sf::Color::White);
                selectedItem = (selectedItem + 1) % startGameOptions.size();
                startGameItems[selectedItem].setFillColor(sf::Color::Red);
            } 
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedItem == 0) {
                    CharacterSelection characterSelection;
                    std::string chosenCharacter = characterSelection.run();
                    
                    Game game(chosenCharacter);
                    game.run();
                }
                menuStack.pop();
            }
        }
    }
}

void StartGameMenu::render(sf::RenderWindow& window) {
    window.clear();
    for (auto& item : startGameItems) {
        window.draw(item);
    }
    window.display();
}

// ---------------- HOW TO PLAY MENU ----------------
HowToPlayMenu::HowToPlayMenu() {
    if (!font.loadFromFile("Pixel Times Bold.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    instructions.setFont(font);
    instructions.setString("Use WASD or Arrow Keys to move.\nPress F to attack.");
    instructions.setCharacterSize(30);
    instructions.setPosition(100, 200);

    backText.setFont(font);
    backText.setString("Press ESC to go back.");
    backText.setCharacterSize(20);
    backText.setPosition(100, 400);
}

void HowToPlayMenu::handleInput(sf::RenderWindow& window, std::stack<std::unique_ptr<Menu>>& menuStack) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Escape) {
            menuStack.pop();
        }
    }
}

void HowToPlayMenu::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(instructions);
    window.draw(backText);
    window.display();
}

// ---------------- GAME MENU HANDLER ----------------
GameMenu::GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu") {
    menuStack.push(std::make_unique<MainMenu>());
}

void GameMenu::run() {
    while (window.isOpen()) {
        menuStack.top()->handleInput(window, menuStack);
        menuStack.top()->render(window);
    }
}
