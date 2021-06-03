#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <tile.hpp>
#include <piece.hpp>
#include <vector>

namespace Chess {
    class Tile;

    class Board {

        public:
        
        std::array<std::array<Tile, 8>, 8> board;

        Board();
        Board(float sideLength);

        std::vector<Piece> setPieces(const sf::Texture& spriteSheet);

    };
}