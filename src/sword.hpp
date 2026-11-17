#pragma once
#include <SFML/Graphics.hpp>

class Sword {
public:
    Sword();

    bool update(
        float dt, const sf::FloatRect& playerBounds,
        bool facingRight, const sf::FloatRect& enemyBounds
    );

    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    sf::Vector2f swingHitboxPosition{};
    
    int framewidth = 0;
    int frameheight = 0;
    
    float attackInterval = 1.f;
    float attackTimer = 0.f;
    float swingDuration = 0.27f;
    float swingTimer = 0.f;
    
    bool swingFacingRight = true;
    bool hitThisSwing = false;
    bool textureLoaded = false;

};