#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "tile.h"

namespace Chess {
    class Tile;

    class Board {

    public:

        std::array<std::array<Tile, 8>, 8> board;

        std::vector<Piece*> pieces;

        Board();
        Board(float sideLength);

        std::vector<Piece *> setPieces(const sf::Texture& spriteSheet);
        
        void movePieceToTile(Chess::Tile& tilePtr, Chess::Piece& piecePtr, std::vector<Chess::Piece*>& pieces);

        void clearHighlights();

        void draw(sf::RenderWindow & window);
    };
}