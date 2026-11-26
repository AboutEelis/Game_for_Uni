#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

struct StaffHit {
    std::size_t targetIndex;
    float damage;
};

class Staff {
public:
    void setLevel(int level);

    std::vector<StaffHit> update(
        float dt,
        sf::Vector2f playerCenter,
        const std::vector<sf::FloatRect>& targets
    );

    void draw(sf::RenderWindow& window) const;

private:
    struct Projectile {
        sf::CircleShape shape;
        sf::Vector2f velocity;
        float damage;
        float lifetime;

        Projectile(sf::Vector2f position, sf::Vector2f direction, float damage);
    };

    std::vector<Projectile> projectiles_;
    float attackTimer_ = 0.f;
    float attackInterval_ = 0.9f;
    float projectileSpeed_ = 270.f;
    int level_ = 1;
};