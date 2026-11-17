#include <SFML/Graphics.hpp>
#include <optional>

#include "enemyManager.hpp"
#include "player.hpp"

int main() {
    const unsigned int width = 800;
    const unsigned int height = 600;
    const sf::Vector2u videoModeSize(width, height);
    const sf::Vector2f windowSize(static_cast<float>(width), static_cast<float>(height));
    sf::RenderWindow window(sf::VideoMode(videoModeSize), "SFML window");

    sf::Clock clock;
    Player player;
    EnemyManager enemyManager(5);
    enemyManager.setPlayer(&player);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        player.update(dt, windowSize);
        enemyManager.update(dt);

        window.clear(sf::Color(106, 153, 78, 255));
        player.draw(window);
        enemyManager.draw(window);
        window.display();
    }

    return 0;
}

