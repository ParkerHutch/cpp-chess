#include <SFML/Graphics.hpp>
#include "tile.h"

namespace Chess {

    Tile::Tile() {
        this->shape = sf::RectangleShape();
    }

    Tile::Tile(float sideLength, int row, int col) {
        this->shape = sf::RectangleShape(sf::Vector2f(sideLength, sideLength));
        this->boardPosition = sf::Vector2i(row, col); // TODO maybe I don't need this
        this->shape.setFillColor(getNormalColor());
    }

    sf::Color Tile::getNormalColor() const {
        return (boardPosition.x + boardPosition.y) % 2 == 0 ? TILE_COLOR_A : TILE_COLOR_B;
    }
}