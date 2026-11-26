#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "progression.hpp"
#include "staff.hpp"
#include "sword.hpp"
#include "aura.hpp"

class Game {
public:
    Game();

    void update(float dt, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);

private:
    void damageEnemy(float amount);

    Player player_;
    Progression progression_;
    Sword sword_;
    Staff staff_;
    Aura aura_;

    sf::RectangleShape enemy_;
    float enemyHealth_ = 50.f;
    bool enemyAlive_ = true;

    float damageCooldown_ = 0.f;
    static constexpr float damageInterval_ = 0.05f;
    static constexpr float damageAmount_ = 1.5f;
};