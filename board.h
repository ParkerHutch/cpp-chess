#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "tile.h"

namespace Chess {

    class Board {

    public:
        
        std::array<std::array<Tile *, 8>, 8> board; // The 8x8 board of Tiles

        std::vector<Piece*> pieces; // All pieces currently on the board

        /**
        * Creates an 8x8 board of alternatingly colored square tiles whose side lengths correspond to 1/8 of the 
        * given side length parameter.
        * 
        * @param sideLength the side length of the entire board
        */
        Board(const float sideLength);

        /**
        * @brief Creates pointers to the standard chess board pieces and stores them in a list.
        * 
        * Pointers to all chess pieces in their standard configurations are created and added to 
        * the pieces list. The spriteSheet parameter is passed to the Piece constructors for loading
        * of their sprites.
        * 
        * @param spriteSheet a sprite sheet of chess piece sprites
        */
        void setPieces(const sf::Texture& spriteSheet);
        
        bool boardPositionOccupied(const sf::Vector2i position) const;


        /**
        * @brief moves a piece to a tile, removing the piece that was previously there if it exists.
        * 
        * Moves the Piece pointed to by piecePtr to the tile pointed to by tilePtr. If tilePtr had a piece
        * it pointed to, that pointer is deleted, and the piece is removed from the board's list of pieces.
        * The tile pointed to by tilePtr is assumed to be a valid move location for the Piece.
        * 
        * @param piecePtr the piece to move
        * @param tilePtr the tile to move the piece to.
        */
        void movePieceToTile(Chess::Piece * piecePtr, Chess::Tile * tilePtr);

        /**
        * Resets the fill color of all tiles to their default fill color. This has the effect of
        * removing any user piece or tile selection effects.
        */
        void resetColors();

        /**
        * Draws the board and its pieces on the given window. 
        */
        void draw(sf::RenderWindow & window) const;
    };
}