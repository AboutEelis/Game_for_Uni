#include <SFML/Graphics.hpp>
#include <algorithm>

int main() {
    // Create the main window
    float width=800, height=600;
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}), "SFML window");

    // Creates rectangle
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(50, 100));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition({10,20});

    // Clock
    sf::Clock clock;
    float speed = 300;
    float dt = 0;
    

    // Start the game loop
    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
    

        // Process events
        while (const std::optional event = window.pollEvent()) {

            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        

        // Move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        {
            rectangle.move({0,-(speed * dt)});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            rectangle.move({0,speed * dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            rectangle.move({-(speed * dt),0});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            rectangle.move({speed * dt,0});
        }

        // Rectangle closed in a window
        sf::Vector2f rect_pos = rectangle.getPosition();
        sf::Vector2f rect_size = rectangle.getSize();
        
        if (rect_pos.x < 0) rect_pos.x = 0;
        if (rect_pos.y < 0) rect_pos.y = 0;
        if (rect_pos.x > (width - rect_size.x)) rect_pos.x = (width - rect_size.x);
        if (rect_pos.y > (height - rect_size.y)) rect_pos.y = (height - rect_size.y);

        rectangle.setPosition(rect_pos);


        // Clear screen with solid color
        window.clear(sf::Color(106, 153, 78, 255));

        window.draw(rectangle);

        // Update window
        window.display();
    }
}