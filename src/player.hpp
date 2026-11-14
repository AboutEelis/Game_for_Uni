#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float dt, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    float speed;
};