#include "enemyManager.hpp"

#include <algorithm>
#include <cmath>
#include <random>

#include "player.hpp"

namespace {
std::mt19937 rng{std::random_device{}()};
}

Enemy::Enemy()
    : speed(80.f + (rng() % 80)), dead(false) {
    shape.setSize({40.f, 40.f});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({
        static_cast<float>(rng() % 700 + 40),
        static_cast<float>(rng() % 500 + 40)
    });
}

bool Enemy::isDead() const {
    return dead;
}

void Enemy::update(float dt, const sf::Vector2f& targetPosition) {
    sf::Vector2f direction = targetPosition - shape.getPosition();
    const float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.0001f) {
        direction /= distance;
        shape.move(direction * speed * dt);
    }

    if (shape.getPosition().y > 700.f) {
        dead = true;
    }
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

EnemyManager::EnemyManager(int maxEnemies)
    : maxEnemies(maxEnemies) {}

void EnemyManager::setPlayer(Player* playerPtr) {
    player = playerPtr;
}

void EnemyManager::spawnEnemy() {
    if (enemies.size() < static_cast<std::size_t>(maxEnemies)) {
        enemies.emplace_back();
    }
}

void EnemyManager::removeDead() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& enemy) {
                return enemy.isDead();
            }),
        enemies.end());
}

void EnemyManager::update(float dt) {
    removeDead();

    while (enemies.size() < static_cast<std::size_t>(maxEnemies)) {
        spawnEnemy();
    }

    if (player != nullptr) {
        for (auto& enemy : enemies) {
            enemy.update(dt, player->getPosition());
        }
    }
}

void EnemyManager::draw(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }
}