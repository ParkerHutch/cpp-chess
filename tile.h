#pragma once

#include <SFML/Graphics.hpp>
#include "piece.h"

namespace Chess {

    class Piece; // Forward declaration to resolve circular dependency

    const sf::Color TILE_COLOR_A = sf::Color::White;
    const sf::Color TILE_COLOR_B = sf::Color::Black;

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