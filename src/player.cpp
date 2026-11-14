#include "player.hpp"
#include <algorithm>

Player::Player() : speed(300.f) {
    shape.setSize({50.f, 100.f});
    shape.setFillColor(sf::Color::Black);
    shape.setPosition({10.f, 20.f});
}

void Player::update(float dt, sf::Vector2f windowSize) {
    // Движение
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        shape.move({0.f, -speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        shape.move({0.f, speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        shape.move({-speed * dt, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        shape.move({speed * dt, 0.f});

    // Не выходить за границы окна
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    pos.x = std::clamp(pos.x, 0.f, windowSize.x - size.x);
    pos.y = std::clamp(pos.y, 0.f, windowSize.y - size.y);
    shape.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}