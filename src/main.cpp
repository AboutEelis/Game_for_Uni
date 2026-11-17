#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "sword.hpp"

int main() {
    // Create the main window
    const unsigned int width = 800;
    const unsigned int height = 600;
    const sf::Vector2f windowSize(static_cast<float>(width), static_cast<float>(height));
    sf::RenderWindow window(sf::VideoMode({width, height}), "SFML window");

    sf::Clock clock;
    Player player;
    Sword sword;

    sf::RectangleShape enemy({40.f, 40.f});
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition({400.f, 300.f});
    float enemyHealth = 50.f;
    bool enemyAlive = true;

    float damageCooldown = 0.f;
    constexpr float damageInterval = 0.05f;
    constexpr float damageAmount = 1.5f;

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

        const sf::FloatRect enemyBounds = enemyAlive ? enemy.getGlobalBounds() : sf::FloatRect{};

        if (sword.update(dt, player.getBounds(), player.isFacingRight(), enemyBounds)) {
            enemyHealth -= 12.f;

            if (enemyHealth <= 0.f) {
                enemyAlive = false;
            }
        }

        if (damageCooldown > 0.f) {
            damageCooldown -= dt;
        }

        const bool touching = enemyAlive && player.getBounds().findIntersection(enemy.getGlobalBounds()).has_value();

        if (touching && damageCooldown <= 0.f) {
            player.takeDamage(damageAmount);
            damageCooldown = damageInterval;
        } else if (!touching) {
            damageCooldown = 0.f;
        }

        // 3.Window dispay
        window.clear(sf::Color(106, 153, 78, 255));
        if (enemyAlive) {
            window.draw(enemy);
        }
        sword.draw(window);
        player.draw(window);
        window.display();
    }
}