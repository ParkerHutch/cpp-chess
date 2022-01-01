#include <SFML/Graphics.hpp>
#include <vector>
#include "board.h"
#include "piece.h"
#include <iostream>

namespace Chess {

    Board::Board(const float sideLength) {
        float tileSideLength = sideLength / 8;

        for (int rowIndex = 0; rowIndex < board.size(); ++rowIndex) {
            for (int colIndex = 0; colIndex < board[rowIndex].size(); ++colIndex) {
                board[rowIndex][colIndex] = Tile(sideLength, rowIndex, colIndex);
                board[rowIndex][colIndex].shape.setPosition(rowIndex * sideLength, colIndex * sideLength);
            }
        }

    }

    void Board::setPieces(const sf::Texture& spriteSheet) {
        int backRankPiecesOrder[8] = {
            Chess::ROOK, Chess::KNIGHT, Chess::BISHOP, Chess::QUEEN,
            Chess::KING, Chess::BISHOP, Chess::KNIGHT, Chess::ROOK
        };
        for (int columnIndex = 0; columnIndex < 8; ++columnIndex) {
            pieces.push_back(new Piece(board[columnIndex][0], WHITE, backRankPiecesOrder[columnIndex], spriteSheet));
            pieces.push_back(new Piece(board[columnIndex][1], WHITE, PAWN, spriteSheet));
            pieces.push_back(new Piece(board[columnIndex][6], BLACK, PAWN, spriteSheet));
            pieces.push_back(new Piece(board[columnIndex][7], BLACK, backRankPiecesOrder[columnIndex], spriteSheet));
        }
        
    }

    bool Board::boardPositionOccupied(const sf::Vector2i position) const {
        return board[position.x][position.y].piecePtr != nullptr;
    }

    void Board::movePieceToTile(Chess::Piece& piecePtr, Chess::Tile& tilePtr) {
        if (tilePtr.piecePtr) {

            if (tilePtr.piecePtr->color != piecePtr.color) {

                // Remove the conquered piece from the game

                Chess::Piece* conqueredPiece = tilePtr.piecePtr;
                auto pieceIndex = std::find(pieces.begin(), pieces.end(), conqueredPiece);
                pieces.erase(pieceIndex);
                delete conqueredPiece;

            }

        }
        piecePtr.moveToTile(tilePtr);
    }

    void Board::clearHighlights() {

        for (auto &row : board) {
            for (auto &tile : row) {
                tile.shape.setFillColor(tile.getNormalColor());
            }
        }

    }

    void Board::draw(sf::RenderWindow & window) const {

        for (auto &row : board) { 
            for (auto &tile : row) {
                window.draw(tile.shape);
            }
        }

        for (auto &piece : pieces) {
            piece->draw(window);
        }

    }

}