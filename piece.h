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
        bool boardPositionOccupied(const sf::Vector2i position, const std::array<std::array<Tile, 8>, 8>& board) const;
        

    public:
        int color;
        int pieceType;
        sf::Sprite sprite;
        Tile* tilePtr; // the Tile this piece occupies

        Piece(const bool color);
        Piece(Tile * initialTilePtr, const int color, const int pieceType);
        Piece(Tile * initialTilePtr, const int color, const int pieceType, const sf::Texture& spriteSheet);


        bool boardPositionOccupiedByEnemy(const sf::Vector2i position, const std::array<std::array<Tile *, 8>, 8>& board) const;

        std::vector<Tile *> getValidMoveTilePtrs(const std::array<std::array<Tile*, 8>, 8>& board) const;


        void moveToTile(Tile * nextTilePtr);

        void draw(sf::RenderWindow& window) const;
        
    };

    /**
    * @brief Get all valid move locations for the given pawn piece.
    *
    * Returns a list of board coordinates corresponding to valid move locations
    * for the given pawn. This includes the tile in front of the pawn if it is
    * empty and the two diagonal spots in front of the pawn if they are
    * occupied by pieces of the opposite color.
    *
    * @param pawnPtr the pawn to get valid move locations for
    * @param board the board containing chess pieces
    *
    * @return a list of coordinates on the board that the pawn is allowed to
    * move to according to chess rules
    *
    */
    std::vector<sf::Vector2i> getPawnPossibleMoves(const Piece* pawnPtr, const std::array<std::array<Tile, 8>, 8>& board);
}