#include <SFML/Graphics.hpp>
#include <tile.hpp>

namespace Chess {

    Tile::Tile() {
        shape = sf::RectangleShape();
    }

    Tile::Tile(sf::Vector2f size, sf::Vector2f boardPosition, sf::Color color) {
        shape = sf::RectangleShape(size);
        this->boardPosition = boardPosition;
        //this->shape.setPosition(position);
        this->shape.setFillColor(color);
    }

}