#include <SFML/Graphics.hpp>
#include <vector>
#include "board.h"
#include "piece.h"
#include <iostream>

namespace Chess {

    Board::Board() {
        for (int rowIndex = 0; rowIndex < board.size(); ++rowIndex) {
            for (int colIndex = 0; colIndex < board[rowIndex].size(); ++colIndex) {
                board[rowIndex][colIndex] = Tile();
            }
        }
    }

    Board::Board(float sideLength) {
        // sideLength: the side length of the entire board (board should be a square)
        float tileSideLength = sideLength / 8;

        for (int rowIndex = 0; rowIndex < board.size(); ++rowIndex) {
            for (int colIndex = 0; colIndex < board[rowIndex].size(); ++colIndex) {
                sf::Color color = (rowIndex + colIndex) % 2 == 0 ? sf::Color::White : sf::Color::Black;
                board[rowIndex][colIndex] = Tile(sideLength, rowIndex, colIndex);
                board[rowIndex][colIndex].shape.setPosition(rowIndex * sideLength, colIndex * sideLength);
            }
        }

    }

    std::vector<Piece *> Board::setPieces(const sf::Texture& spriteSheet) {
        //std::vector<Piece *> pieces;
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
        
        return pieces;
    }

    void Board::movePieceToTile(Chess::Tile& tilePtr, Chess::Piece& piecePtr, std::vector<Chess::Piece*>& pieces) {
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

        for (auto& row : board) {
            for (auto& tile : row) {
                tile.shape.setFillColor(tile.getNormalColor());
            }
        }

    }

    void Board::draw(sf::RenderWindow & window) {

        // Draw the chess board
        for (auto row : board) { // TODO this should be a method inside board
            for (auto tile : row) {
                window.draw(tile.shape);
            }
        }
        // Draw the pieces
        for (auto piece : pieces) {

            window.draw(piece->sprite);

        }

    }

}