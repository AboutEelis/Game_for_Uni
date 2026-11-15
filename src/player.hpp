#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float dt, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;

    // Анимация ходьбы
    int currentFrame = 0; // Текущий кадр
    float animTimer = 0.f; // Сколько сек показывается текущий кадр
    float frameTime = 0.15f; // Сколько сек длится один кадр
    int frameCount = 4; // Сколько всего кадров
    int frameWidth = 174;
    int frameHeight = 198;

    // Разворот влево вправо
    bool facingRight = true;
};