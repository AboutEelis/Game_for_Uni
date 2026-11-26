#include "game.hpp"

#include <cstddef>
#include <vector>

Game::Game() {
    enemies_.setPlayer(&player_);
}

void Game::update(float dt, sf::Vector2f windowSize) {
    player_.update(dt, windowSize);

    enemies_.update(dt);

    const sf::FloatRect playerBounds = player_.getBounds();
    const sf::Vector2f playerCenter{
            playerBounds.position.x + playerBounds.size.x / 2.f,
            playerBounds.position.y + playerBounds.size.y / 2.f
    };

    // Список целей для оружия.
    // Индекс в списке = номер врага.
    const std::vector<sf::FloatRect> targets = enemies_.getBounds();

    // Меч
    for (std::size_t index : sword_.update(dt, playerBounds, player_.isFacingRight(), targets))
        enemies_.damageEnemy(index, 12.f);

    // Посох работает после того, как его выбрали в прокачке.(1 пока заглушка)
    const int staffLevel = 1;

    if (staffLevel > 0) {
        staff_.setLevel(staffLevel);

        for (const StaffHit& hit : staff_.update(dt, playerCenter, targets)) {
                enemies_.damageEnemy(hit.targetIndex, hit.damage);
        }
    }

    // Аура
    const int auraLevel = 1;

    if (auraLevel > 0) {
        aura_.setLevel(auraLevel);

        for (const StaffHit& hit : aura_.update(dt, playerCenter, targets)) {
                enemies_.damageEnemy(hit.targetIndex, hit.damage);
        }
    }

    if (damageCooldown_ > 0.f)
        damageCooldown_ -= dt;

    bool touching = false;
    for (const sf::FloatRect& target : targets) {
        if (target.size.x > 0.f && target.size.y > 0.f &&
        playerBounds.findIntersection(target).has_value()) {
            touching = true;
            break;
        }
    }

    if (touching && damageCooldown_ <= 0.f) {
        player_.takeDamage(damageAmount_);
        damageCooldown_ = damageInterval_;
    } else if (!touching) {
        damageCooldown_ = 0.f;
    }
}

void Game::draw(sf::RenderWindow& window) {
    aura_.draw(window);
    enemies_.draw(window);
    staff_.draw(window);
    sword_.draw(window);
    player_.draw(window);
}