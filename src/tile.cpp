#include <SFML/Graphics.hpp>
#include <tile.hpp>

namespace Chess {

    Tile::Tile() {
        shape = sf::RectangleShape();
    }

    Tile::Tile(float sideLength, int row, int col, sf::Color color) {
        shape = sf::RectangleShape(sf::Vector2f(sideLength, sideLength));
        this->shape.setFillColor(color);
        this->shape.setOutlineColor(sf::Color::Black);
        this->shape.setOutlineThickness(-1);
        boardPosition = sf::Vector2f(row, col);
    }

}