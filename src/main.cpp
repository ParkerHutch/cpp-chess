#include <SFML/Graphics.hpp>

const sf::Vector2f windowDimensions(800, 800);

int main() {
    sf::RenderWindow window(sf::VideoMode(windowDimensions.x, windowDimensions.y),
                            "Chess++");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}