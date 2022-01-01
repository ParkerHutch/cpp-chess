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

        }
        break;

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

    

}