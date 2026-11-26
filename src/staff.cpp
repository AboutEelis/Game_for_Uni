#include "staff.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

Staff::Projectile::Projectile(
    sf::Vector2f position,
    sf::Vector2f direction,
    float projectileDamage
)
    : shape(7.f),
    velocity(direction),
    damage(projectileDamage),
    lifetime(3.f) {
        shape.setOrigin({7.f, 7.f});
        shape.setPosition(position);
        shape.setFillColor(sf::Color(180, 90, 255));
}

void Staff::setLevel(int level) {
    level_ = std::clamp(level, 1, 8);
}

std::vector<StaffHit> Staff::update(
    float dt,
    sf::Vector2f playerCenter,
    const std::vector<sf::FloatRect>& targets
) {
    attackTimer_ = std::min(attackTimer_ + dt, attackInterval_);

    if (attackTimer_ >= attackInterval_) {
        std::size_t nearestIndex = targets.size();
        float nearestDistanceSquared = std::numeric_limits<float>::max();

        for (std::size_t i = 0; i < targets.size(); ++i) {
            const sf::FloatRect& target = targets[i];

            if (target.size.x <= 0.f || target.size.y <= 0.f)
                continue;

            const sf::Vector2f targetCenter{
                target.position.x + target.size.x / 2.f,
                target.position.y + target.size.y / 2.f,
            };

            const float dx = targetCenter.x - playerCenter.x;
            const float dy = targetCenter.y - playerCenter.y;
            const float distanceSquared = dx * dx + dy * dy;

            if (distanceSquared < nearestDistanceSquared) {
                nearestDistanceSquared = distanceSquared;
                nearestIndex = i;
            }
        }

        if (nearestIndex != targets.size()) {
            const sf::FloatRect& target = targets[nearestIndex];
            const sf::Vector2f targetCenter{
                target.position.x + target.size.x / 2.f,
                target.position.y + target.size.y / 2.f
            };

            const float dx = targetCenter.x - playerCenter.x;
            const float dy = targetCenter.y - playerCenter.y;
            const float distance = std::sqrt(dx*dx + dy*dy);

            if (distance > 0.f) {
                const sf::Vector2f direction{dx / distance, dy / distance};
                const float damage = 8.f + 3.f * static_cast<float>(level_ - 1);

                projectiles_.emplace_back(playerCenter, direction, damage);
                attackTimer_ = 0.f;
            }
        }
    }

    std::vector<StaffHit> hits;
    std::vector<bool> targetAlreadyHit(targets.size(), false);

    for (std::size_t i = 0; i < projectiles_.size();) {
        Projectile& projectile = projectiles_[i];
        projectile.shape.move(projectile.velocity * projectileSpeed_ * dt);
        projectile.lifetime -= dt;

        std::size_t hitIndex = targets.size();
        float closestHitDistanceSquared = std::numeric_limits<float>::max();

        for (std::size_t j = 0; j < targets.size(); ++j) {
            if (targetAlreadyHit[j])
                continue;

            const sf::FloatRect& target = targets[j];

            if (target.size.x <= 0.f || target.size.y <= 0.f)
                continue;

            if (!projectile.shape.getGlobalBounds()
                     .findIntersection(target)
                     .has_value()) {
                continue;
            }

            const sf::Vector2f targetCenter{
                target.position.x + target.size.x / 2.f,
                target.position.y + target.size.y / 2.f
            };

            const sf::Vector2f projectileCenter = projectile.shape.getPosition();
            const float dx = targetCenter.x - projectileCenter.x;
            const float dy = targetCenter.y - projectileCenter.y;
            const float distanceSquared = dx * dx + dy * dy;

            if (distanceSquared < closestHitDistanceSquared) {
                closestHitDistanceSquared = distanceSquared;
                hitIndex = j;
            }
        }

        if (hitIndex != targets.size()) {
            hits.push_back({hitIndex, projectile.damage});
            targetAlreadyHit[hitIndex] = true;
            projectiles_.erase(projectiles_.begin() + static_cast<std::ptrdiff_t>(i));
        } else if (projectile.lifetime <= 0.f) {
            projectiles_.erase(projectiles_.begin() + static_cast<std::ptrdiff_t>(i));
        } else {
            ++i;
        }
    }

    return hits;
}

void Staff::draw(sf::RenderWindow& window) const {
    for (const Projectile& projectile : projectiles_)
        window.draw(projectile.shape);
}