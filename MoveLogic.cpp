#include "MoveLogic.h"
#include "piece.h"
#include "tile.h"
#include <iostream>
#include <array>

namespace Chess {
    
    std::vector<Tile*> MoveLogic::getValidMoveTilePtrs(const Piece & piece, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile*> results;
        sf::Vector2i currentPosition = piece.tilePtr->boardPosition;
        switch (piece.pieceType) {
        case PAWN:
        {
            results = getPawnPossibleMovePtrs(piece, board);
            break;
        }
        case KING:
        {
            results = getKingPossibleMovePtrs(piece, board);
            break;
        }

        default:
            std::cout << "Selected piece has no type so default case is happening, bad\n";
            break;
        }
        return results;

    }

    std::vector<Tile*> MoveLogic::getPawnPossibleMovePtrs(const Piece& pawn, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile*> results;
        sf::Vector2i currentPosition = pawn.tilePtr->boardPosition;

        sf::Vector2i forwards(currentPosition.x, currentPosition.y + 1 - 2 * pawn.color);
        if (forwards.y >= 0 && forwards.y <= 7) {
            if (board[forwards.x][forwards.y]->piecePtr == nullptr) {
                results.push_back(board[forwards.x][forwards.y]);
            }
            if (currentPosition.x > 0) {
                sf::Vector2i leftDiagonal(currentPosition.x - 1, currentPosition.y + 1 - 2 * pawn.color);
                if (pawn.tileOccupiedByEnemy(board[leftDiagonal.x][leftDiagonal.y])) {
                    results.push_back(board[leftDiagonal.x][leftDiagonal.y]);
                }
            }

            if (currentPosition.x <= 6) {
                sf::Vector2i rightDiagonal(currentPosition.x + 1, currentPosition.y + 1 - 2 * pawn.color);
                if (pawn.tileOccupiedByEnemy(board[rightDiagonal.x][rightDiagonal.y])) {
                    results.push_back(board[rightDiagonal.x][rightDiagonal.y]);
                }
            }
        }

        return results;

    }

    std::vector<Tile*> MoveLogic::getKingPossibleMovePtrs(const Piece& king, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile*> results;
        sf::Vector2i currentPosition = king.tilePtr->boardPosition;

        sf::Vector2i forwards(currentPosition.x, currentPosition.y + 1 - 2 * king.color);

        for (int x = -1; x <= 1; x++) {

            for (int y = -1; y <= 1; y++) {

                sf::Vector2i checkPosition(currentPosition.x + x, currentPosition.y + y);
                // Make sure prospective tile is within the bounds of the board
                if (checkPosition.x >= 0 && checkPosition.x <= 7 && checkPosition.y >= 0 && checkPosition.y <= 7 && currentPosition != checkPosition) {
                    Tile* checkTilePtr = board[checkPosition.x][checkPosition.y];
                    if (!checkTilePtr->piecePtr || king.tileOccupiedByEnemy(checkTilePtr)) {

                        results.push_back(checkTilePtr);
                    }
                }
            }
        }
        
        return results;
    }

    std::vector<Tile*> MoveLogic::getRookPossibleMovePtrs(const Piece& pawn, const std::array<std::array<Tile*, 8>, 8>& board)
    {
        return std::vector<Tile*>();
    }

    std::vector<Tile*> MoveLogic::getKnightPossibleMovePtrs(const Piece& pawn, const std::array<std::array<Tile*, 8>, 8>& board)
    {
        return std::vector<Tile*>();
    }

    std::vector<Tile*> MoveLogic::getBishopPossibleMovePtrs(const Piece& bishop, const std::array<std::array<Tile*, 8>, 8>& board)
    {
        return std::vector<Tile*>();
    }

    std::vector<Tile*> MoveLogic::getQueenPossibleMovePtrs(const Piece& queen, const std::array<std::array<Tile*, 8>, 8>& board)
    {
        return std::vector<Tile*>();
    }

    

}