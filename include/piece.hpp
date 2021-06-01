#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <tile.hpp>


namespace Chess {

    // TODO maybe put piece constants in their own file
    const int PAWN = 0;

    class Tile; // Forward declaration to resolve circular dependency

    class Piece {
        public:
            //const int pieceType;
            // Board * boardPtr = 0; // used to determine move positions
            Tile * tilePtr = 0; // the Tile this piece occupies
            
            Piece();
            Piece(Tile& tile);

            std::vector<sf::Vector2f> getMovePositions();
        
    };
}