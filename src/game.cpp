#include "game.hpp"

#include <vector>

Game::Game() {
    enemy_.setSize({40.f, 40.f});
    enemy_.setFillColor(sf::Color::Red);
    enemy_.setPosition({400.f, 300.f});
}

void Game::damageEnemy(float amount) {
    if (!enemyAlive_)
        return;

    enemyHealth_ -= amount;

    if (enemyHealth_ <= 0.f)
        enemyAlive_ = false;
}

void Game::update(float dt, sf::Vector2f windowSize) {
    player_.update(dt, windowSize);

    const sf::FloatRect playerBounds = player_.getBounds();
    const sf::FloatRect enemyBounds =
        enemyAlive_ ? enemy_.getGlobalBounds() : sf::FloatRect{};

    const sf::Vector2f playerCenter{
            playerBounds.position.x + playerBounds.size.x / 2.f,
            playerBounds.position.y + playerBounds.size.y / 2.f
    };

    // Список целей для дальнобойного оружия (посох, аура).
    // Индекс в списке = номер врага.
    const std::vector<sf::FloatRect> targets{enemyBounds};

    if (sword_.update(dt, playerBounds, player_.isFacingRight(), enemyBounds))
        damageEnemy(12.f);

    // Посох работает после того, как его выбрали в прокачке.(1 пока заглушка)
    const int staffLevel = 1;

    if (staffLevel > 0) {
        staff_.setLevel(staffLevel);

        for (const StaffHit& hit : staff_.update(dt, playerCenter, targets)) {
            if (hit.targetIndex == 0)
                damageEnemy(hit.damage);
        }
    }

    const int auraLevel = 1;

    if (auraLevel > 0) {
        aura_.setLevel(auraLevel);

        for (const StaffHit& hit : aura_.update(dt, playerCenter, targets)) {
            if (hit.targetIndex == 0)
                damageEnemy(hit.damage);
        }
    }

    if (damageCooldown_ > 0.f)
        damageCooldown_ -= dt;

    const bool touching =
        enemyAlive_ &&
        playerBounds.findIntersection(enemy_.getGlobalBounds()).has_value();

    if (touching && damageCooldown_ <= 0.f) {
        player_.takeDamage(damageAmount_);
        damageCooldown_ = damageInterval_;
    } else if (!touching) {
        damageCooldown_ = 0.f;
    }
}

void Game::draw(sf::RenderWindow& window) {
    aura_.draw(window);

    if (enemyAlive_)
        window.draw(enemy_);

    staff_.draw(window);
    sword_.draw(window);
    player_.draw(window);
}