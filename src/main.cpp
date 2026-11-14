#include <SFML/Graphics.hpp>
#include "player.hpp"

int main() {
    // Create the main window
    const unsigned int width = 800;
    const unsigned int height = 600;
    const sf::Vector2f windowSize(static_cast<float>(width), static_cast<float>(height));
    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML window");

    sf::Clock clock;
    Player player;

    // Start the game loop
    while (window.isOpen()) {
    

        // 1.Process events
        while (const std::optional event = window.pollEvent()) {

            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 2.Update
        float dt = clock.restart().asSeconds();
        player.update(dt, windowSize);

        // 3.Window dispay
        window.clear(sf::Color(106, 153, 78, 255));
        player.draw(window);
        window.display();
    }
}