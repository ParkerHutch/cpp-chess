#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <tile.hpp>

namespace Chess {
    class Tile;

    class Board {

        public:
        std::array<std::array<Tile, 8>, 8> board;

        Board();
        Board(float sideLength);

    };
}