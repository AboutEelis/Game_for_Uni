#include "aura.hpp"

#include <algorithm>

Aura::Aura() {
    shape_.setPointCount(60);
    shape_.setFillColor(sf::Color(255, 220, 80, 60));
    shape_.setOutlineColor(sf::Color(255, 220, 80, 160));
    shape_.setOutlineThickness(2.f);
}

void Aura::setLevel(int level) {
    level_ = std::clamp(level, 1, 8);
}

std::vector<StaffHit> Aura::update(
    float dt,
    sf::Vector2f playerCenter,
    const std::vector<sf::FloatRect>& targets
) {
    const float levelBonus = static_cast<float>(level_ -1);
    radius_ = 90.f + 12.f * levelBonus;
    const float damage = 4.f + 1.5f * levelBonus;

    shape_.setRadius(radius_);
    shape_.setOrigin({radius_, radius_});
    shape_.setPosition(playerCenter);

    std::vector<StaffHit> hits;

    tickTimer_ += dt;
    while (tickTimer_ >= tickInterval_) {
        tickTimer_ -= tickInterval_;

        for (std::size_t i = 0; i < targets.size(); ++i) {
            const sf::FloatRect& target = targets[i];

            if(target.size.x <= 0.f || target.size.y <= 0.f)
                continue;

            const float dx = target.position.x + target.size.x / 2.f - playerCenter.x;
            const float dy = target.position.y + target.size.y / 2.f - playerCenter.y;

            if (dx*dx + dy*dy <= radius_ * radius_)
                hits.push_back({i, damage});
        }
    }

    return hits;
}

void Aura::draw(sf::RenderWindow& window) const {
    window.draw(shape_);
}