#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float dt, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const {
    return shape.getPosition();}

private:
    sf::RectangleShape shape;
    float speed;
};