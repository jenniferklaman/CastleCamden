#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class GameMenu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    std::vector<std::string> characters = {"Jen", "Eden", "Ale", "Alyssa"};
    int selectedItem = 0;

public:
    GameMenu() : window(sf::VideoMode(800, 600), "Castle Camden - Main Menu") {
        if (!font.loadFromFile("retro_font.ttf")) {
            std::cerr << "Error loading font!\n";
        }

        // Title
        title.setFont(font);
        title.setString("Castle Camden");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(250, 50);

        // Menu Items
        for (size_t i = 0; i < characters.size(); i++) {
            sf::Text text;
            text.setFont(font);
            text.setString(characters[i]);
            text.setCharacterSize(40);
            text.setPosition(300, 200 + (i * 50));
            text.setFillColor((i == 0) ? sf::Color::Red : sf::Color::White);
            menuItems.push_back(text);
        }
    }

    void run() {
        while (window.isOpen()) {
            handleInput();
            render();
        }
    }

private:
    void handleInput() {
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
                    std::cout << "Character Selected: " << characters[selectedItem] << std::endl;
                }
            }
        }
    }

    void navigateMenu(int direction) {
        menuItems[selectedItem].setFillColor(sf::Color::White);
        selectedItem = (selectedItem + direction + characters.size()) % characters.size();
        menuItems[selectedItem].setFillColor(sf::Color::Red);
    }

    void render() {
        window.clear();
        window.draw(title);
        for (auto& item : menuItems) {
            window.draw(item);
        }
        window.display();
    }
};

int main() {
    GameMenu menu;
    menu.run();
    return 0;
}
