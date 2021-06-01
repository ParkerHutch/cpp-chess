#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <tile.hpp>

namespace Chess {
    class Board {

        public:
        std::vector<Tile*> board;

        Board();
        Board(float width, float height);
        
        void draw();

    };
}