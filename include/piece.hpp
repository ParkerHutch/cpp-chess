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
            int pieceType;
            sf::RectangleShape shape;
            //const int pieceType;
            // Board * boardPtr = 0; // used to determine move positions
            Tile * tilePtr; // the Tile this piece occupies
            
            Piece();
            Piece(Tile& tile, const int pieceType);

            std::vector<sf::Vector2f> getMovePositions();

            void draw();
        
    };
}