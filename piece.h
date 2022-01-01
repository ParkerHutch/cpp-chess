#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include <functional>

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
        const int spriteTextureWidth = 45; // TODO declare these somewhere else
        const int spriteTextureHeight = 45;

        void loadSprite(const sf::Texture& spriteSheet);
        

    public:
        int color;
        int pieceType;
        sf::Sprite sprite; // TODO make this a pointer? Might cut down on stack space usage
        Tile* tilePtr; // the Tile this piece occupies

        Piece(const bool color);
        Piece(Tile * initialTilePtr, const int color, const int pieceType);
        Piece(Tile * initialTilePtr, const int color, const int pieceType, const sf::Texture& spriteSheet);

        bool tileOccupiedByEnemy(const Tile* tilePtr) const;

        void moveToTile(Tile * nextTilePtr);

        void draw(sf::RenderWindow& window) const;
        
    };
}