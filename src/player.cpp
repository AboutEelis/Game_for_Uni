#include "player.hpp"
#include <algorithm>
#include <iostream>

Player::Player() : sprite(texture), speed(300.f) {
    if (!texture.loadFromFile("assets/player_walk.png")) {
        std::cerr << "Не удалось загрузить assets/player_walk.png\n";
    }

    sprite.setTextureRect(sf::IntRect({0,0}, {frameWidth, frameHeight}));
    sprite.setOrigin({frameWidth/2.f, frameHeight/2.f});
    sprite.setPosition({200.f, 300.f});
    sprite.setScale({0.5f, 0.5f});
}

void Player::update(float dt, sf::Vector2f windowSize) {
    bool moving = false;

    bool up    = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up);
    bool down  = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down);
    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right);
    // Движение
    if (up){
        sprite.move({0.f, -speed * dt});
        moving = true;
    }
    if (down){
        sprite.move({0.f, speed * dt});
        moving = true;
    }
    if (left){
        sprite.move({-speed * dt, 0.f});
        moving = true;
        facingRight = false;
    }
    if (right){
        sprite.move({speed * dt, 0.f});
        moving = true;
        facingRight = true;
    }

    if (moving) {
        animTimer += dt;
        while (animTimer >= frameTime) {
            animTimer -= frameTime;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    } else {
        animTimer = 0.f;
        currentFrame = 0;
    }

    sprite.setTextureRect(sf::IntRect({currentFrame * frameWidth, 0}, {frameWidth, frameHeight}));
    sprite.setScale({facingRight ? 0.5f : -0.5f, 0.5f});
    

    // Не выходить за границы окна
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f half = sprite.getGlobalBounds().size / 2.f;
    pos.x = std::clamp(pos.x, half.x, windowSize.x - half.x);
    pos.y = std::clamp(pos.y, half.y, windowSize.y - half.y);
    sprite.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}