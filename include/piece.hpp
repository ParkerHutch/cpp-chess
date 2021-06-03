#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <tile.hpp>


namespace Chess {

    // TODO maybe put piece constants in their own file
    const bool WHITE = 0;
    const bool BLACK = 1;

    const int KING = 0;
    const int QUEEN = 1;
    const int BISHOP = 2;
    const int KNIGHT = 3;
    const int ROOK = 4;
    const int PAWN = 5;

    class Tile; // Forward declaration to resolve circular dependency

    class Piece {
        void loadSprite(const sf::Texture& spriteSheet);

        public:
            bool color;
            int pieceType;
            sf::Sprite sprite;
            // Board * boardPtr = 0; // used to determine move positions
            Tile * tilePtr; // the Tile this piece occupies
            
            Piece(bool color);
            Piece(Tile& tile, bool color, const int pieceType);
            Piece(Tile& tile, bool color, const int pieceType, const sf::Texture& spriteSheet);

            std::vector<sf::Vector2f> getMovePositions();

            void draw();
        
    };
}