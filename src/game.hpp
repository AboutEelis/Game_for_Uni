#pragma once

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "enemyManager.hpp"
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
    Player player_;
    Progression progression_;
    Sword sword_;
    Staff staff_;
    Aura aura_;
    EnemyManager enemies_{5};

    float damageCooldown_ = 0.f;
    static constexpr float damageInterval_ = 0.05f;
    static constexpr float damageAmount_ = 1.5f;
};