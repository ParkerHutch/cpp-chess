#pragma once

#include <SFML/Graphics.hpp>
#include <piece.hpp>

namespace Chess {

    class Piece; // Forward declaration to resolve circular dependency

    class Tile {
        public:
            Piece * piecePtr = 0; // The piece on this tile, if there is one // TODO this is probably not needed
            sf::Vector2i boardPosition;
            sf::RectangleShape shape;

            Tile();
            Tile(float sideLength, int row, int col);
            sf::Color getNormalColor();
    };
}