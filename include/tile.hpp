#pragma once

#include <SFML/Graphics.hpp>
#include <piece.hpp>

namespace Chess {

    class Piece; // Forward declaration to resolve circular dependency

    class Tile {
        public:
            Piece * piecePtr; // The piece on this tile, if there is one
            sf::Vector2f boardPosition;
            sf::RectangleShape shape;

            Tile();
            Tile(float sideLength, int row, int col, sf::Color color);
    };
}