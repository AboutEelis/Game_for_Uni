#pragma once

#include <cstddef>
#include <vector>
#include <SFML/Graphics.hpp>

class Player;

class Enemy {
public:
    Enemy();
    void update(float dt, const sf::Vector2f& targetPosition);
    void draw(sf::RenderWindow& window) const;
    bool isDead() const;

    void takeDamage(float amount);
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
    float speed;
    float health;
    bool dead;
};

class EnemyManager {
public:
    explicit EnemyManager(int maxEnemies);
    void setPlayer(Player* player);
    void spawnEnemy();
    void removeDead();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    std::vector<sf::FloatRect> getBounds() const;
    void damageEnemy(std::size_t index, float amount);

private:
    std::vector<Enemy> enemies;
    int maxEnemies;
    Player* player = nullptr;
};