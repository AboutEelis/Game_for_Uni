#include "sword.hpp"
#include <algorithm>
#include <iostream>
#include <string>

Sword::Sword() : sprite(texture) {
    hitbox.setSize({80.f, 35.f});
    
    if (!texture.loadFromFile(std::string(ASSETS_DIR) + "swordslash.png")) {
        std::cerr << "Не удалось загрузить assets/swordslash.png\n";
        return;
    }

    textureLoaded = true;

    const auto sheetSize = texture.getSize();
    framewidth = static_cast<int>(sheetSize.x / 3);
    frameheight = static_cast<int>(sheetSize.y / 3);

    sprite.setOrigin({framewidth / 2.f, frameheight / 2.f});
}

std::vector<std::size_t> Sword::update(
    float dt, const sf::FloatRect& playerBounds,
    bool facingRight, const std::vector<sf::FloatRect>& targets)
{
    attackTimer += dt;

    if (swingTimer > 0.f) {
        swingTimer = std::max(0.f, swingTimer - dt);
    }

    const sf::Vector2f hitboxSize = hitbox.getSize();
    const float playerAttackX = facingRight  
            ? playerBounds.position.x + playerBounds.size.x
            : playerBounds.position.x - hitboxSize.x;
    const float playerAttackY = playerBounds.position.y + (playerBounds.size.y - hitboxSize.y) / 2.f;

    if (swingTimer <= 0.f && attackTimer >= attackInterval) {
        attackTimer = 0.f;
        swingTimer = swingDuration;
        alreadyHit.clear();

        swingHitboxPosition = {playerAttackX, playerAttackY};
        swingFacingRight = facingRight;
    }

    if (swingTimer <= 0.f) {
        return {};
    }

    const float elapsed = swingDuration - swingTimer;
    const float frameDuration = swingDuration / 9.f;
    const int frame = std::min(static_cast<int>(elapsed / frameDuration), 8);

    if (textureLoaded) {
        const int column = frame % 3;
        const int row = frame / 3;

        sprite.setTextureRect(sf::IntRect(
            {column * framewidth, row * frameheight},
            {framewidth, frameheight}
        ));
    }

    hitbox.setPosition(swingHitboxPosition);

    if(textureLoaded) {
        const float scaleX = 100.f / static_cast<float>(framewidth);
        const float scaleY = 100.f / static_cast<float>(frameheight);

        sprite.setScale({swingFacingRight ? scaleX : -scaleX, scaleY});
        sprite.setPosition({
            swingHitboxPosition.x + hitboxSize.x / 2.f,
            swingHitboxPosition.y + hitboxSize.y / 2.f
        });
    }

    const bool damageWindow = elapsed >= swingDuration / 3.f && elapsed <swingDuration * 2.f / 3.f;

    std::vector<std::size_t> hits;

    if (damageWindow) {
        const sf::FloatRect hitboxBounds = hitbox.getGlobalBounds();

        for (std::size_t i=0; i < targets.size(); ++i) {
            const sf::FloatRect& target = targets[i];

            if (target.size.x <= 0.f || target.size.y <= 0.f)
                continue;

            if (std::find(alreadyHit.begin(), alreadyHit.end(), i) != alreadyHit.end())
                continue;

            if (hitboxBounds.findIntersection(target).has_value()) {
                alreadyHit.push_back(i);
                hits.push_back(i);
            }
        }
    }

    return hits;
}

void Sword::draw(sf::RenderWindow& window) const {
    if (swingTimer > 0.f && textureLoaded) {
        window.draw(sprite);
    }
}