#include <SFML/Graphics.hpp>
#include <tile.hpp>
#include <iostream>

namespace Chess {

    Tile::Tile() {
        shape = sf::RectangleShape();
    }

    Tile::Tile(float sideLength, int row, int col) {
        shape = sf::RectangleShape(sf::Vector2f(sideLength, sideLength));
        this->boardPosition = sf::Vector2i(row, col); // TODO maybe I don't need this
        this->shape.setFillColor(getNormalColor());
        //this->shape.setOutlineColor(sf::Color::Black);
        //this->shape.setOutlineThickness(2);
    }

    sf::Color Tile::getNormalColor() {
        return (boardPosition.x + boardPosition.y) % 2 == 0 ? sf::Color::White : sf::Color::Black;
    }
}