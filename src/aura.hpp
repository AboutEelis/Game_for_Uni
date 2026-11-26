#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "staff.hpp"

class Aura {
public:
    Aura();

    void setLevel(int level);

    std::vector<StaffHit> update(
        float dt,
        sf::Vector2f playerCenter,
        const std::vector<sf::FloatRect>& targets
    );

    void draw(sf::RenderWindow& window) const;

private:
    sf::CircleShape shape_;
    float radius_ = 90.f;
    float tickTimer_ = 0.f;
    float tickInterval_ = 1.f;
    int level_ = 1;
};