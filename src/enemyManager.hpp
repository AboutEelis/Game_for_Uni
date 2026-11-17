#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Player;

class Enemy {
public:
    Enemy();
    void update(float dt, const sf::Vector2f& targetPosition);
    void draw(sf::RenderWindow& window) const;
    bool isDead() const;

private:
    sf::RectangleShape shape;
    float speed;
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

private:
    std::vector<Enemy> enemies;
    int maxEnemies;
    Player* player = nullptr;
};