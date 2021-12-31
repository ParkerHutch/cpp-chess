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
        void loadSprite(const sf::Texture& spriteSheet);
        bool boardPositionOccupied(sf::Vector2i position, std::array<std::array<Tile, 8>, 8>& board);
        bool boardPositionOccupiedByEnemy(const sf::Vector2i position, const std::array<std::array<Tile, 8>, 8>& board);

    public:
        int color;
        int pieceType;
        sf::Sprite sprite;
        // Board * boardPtr = 0; // used to determine move positions
        Tile* tilePtr; // the Tile this piece occupies

        Piece(bool color);
        Piece(Tile& tile, int color, const int pieceType);
        Piece(Tile& tile, int color, const int pieceType, const sf::Texture& spriteSheet);

        std::vector<Tile*> getValidMoveTilesPtrs(std::array<std::array<Tile, 8>, 8>& board);

        std::vector<std::reference_wrapper<Tile>> getValidMoveTiles(std::array<std::array<Tile, 8>, 8>& board);

        std::vector<sf::Vector2i> getValidMoveCoordinates(std::array<std::array<Tile, 8>, 8>& board);

        void moveToTile(Tile& tile);

        void draw();

    };
}