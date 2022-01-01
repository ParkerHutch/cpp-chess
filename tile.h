#pragma once

#include <SFML/Graphics.hpp>
#include "piece.h"

namespace Chess {

    class Piece; // Forward declaration to resolve circular dependency

    class Tile {
    public:
        Piece* piecePtr = nullptr; // The piece on this tile, if there is one
        sf::Vector2i boardPosition;
        sf::RectangleShape shape;

        Tile();
        Tile(float sideLength, int row, int col);
        sf::Color getNormalColor() const;
    };
}