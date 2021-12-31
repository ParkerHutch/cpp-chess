#include <SFML/Graphics.hpp>
#include <tile.hpp>

namespace Chess {

    Tile::Tile() {
        this->shape = sf::RectangleShape();
    }

    Tile::Tile(float sideLength, int row, int col) {
        this->shape = sf::RectangleShape(sf::Vector2f(sideLength, sideLength));
        this->boardPosition = sf::Vector2i(row, col); // TODO maybe I don't need this
        this->shape.setFillColor(getNormalColor());
        //this->shape.setOutlineColor(sf::Color::Black);
        //this->shape.setOutlineThickness(2);
    }

    sf::Color Tile::getNormalColor() {
        return (boardPosition.x + boardPosition.y) % 2 == 0 ? sf::Color::White : sf::Color::Black;
    }
}