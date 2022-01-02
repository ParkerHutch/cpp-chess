#include "movelogic.h"
#include "piece.h"
#include "tile.h"
#include <array>
#include <cmath>

namespace Chess {
    
    bool isInside(sf::Vector2i position) {
        return position.x >= 0 && position.x <= 7 && position.y >= 0 && position.y <= 7;
    }

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
        case ROOK:
        {
            results = getRookPossibleMovePtrs(piece, board);
            break;
        }
        case KNIGHT:
        {
            results = getKnightPossibleMovePtrs(piece, board);
            break;
        }
        case BISHOP:
        {
            results = getBishopPossibleMovePtrs(piece, board);
            break;
        }
        case QUEEN:
        {
            results = getQueenPossibleMovePtrs(piece, board);
            break;
        }
        default:
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

            if ((currentPosition.y == 1 && pawn.color == Chess::WHITE) || 
                (currentPosition.y == 6 && pawn.color == Chess::BLACK)) {

                forwards.y += 1 - 2 * pawn.color;

                if (board[forwards.x][forwards.y]->piecePtr == nullptr) {
                    results.push_back(board[forwards.x][forwards.y]);
                }
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

    std::vector<Tile*> MoveLogic::getRookPossibleMovePtrs(const Piece& rook, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile*> results;
        sf::Vector2i currentPosition = rook.tilePtr->boardPosition;

        sf::Vector2i upColumn(currentPosition.x, currentPosition.y - 1);
        while (upColumn.y >= 0 && !rook.tileOccupiedByFriendly(board[upColumn.x][upColumn.y])) {
            
            results.push_back(board[upColumn.x][upColumn.y]);
            if (rook.tileOccupiedByEnemy(board[upColumn.x][upColumn.y])) {
                break;
            }
            upColumn.y--;
        }

        sf::Vector2i downColumn(currentPosition.x, currentPosition.y + 1);
        while (downColumn.y <= 7 && !rook.tileOccupiedByFriendly(board[downColumn.x][downColumn.y])) {

            results.push_back(board[downColumn.x][downColumn.y]);
            if (rook.tileOccupiedByEnemy(board[downColumn.x][downColumn.y])) {
                break;
            }
            downColumn.y++;
        }

        sf::Vector2i leftRow(currentPosition.x - 1, currentPosition.y);
        while (leftRow.x >= 0 && !rook.tileOccupiedByFriendly(board[leftRow.x][leftRow.y])) {

            results.push_back(board[leftRow.x][leftRow.y]);
            if (rook.tileOccupiedByEnemy(board[leftRow.x][leftRow.y])) {
                break;
            }
            leftRow.x--;
        }

        sf::Vector2i rightRow(currentPosition.x + 1, currentPosition.y);
        while (rightRow.x <= 7 && !rook.tileOccupiedByFriendly(board[rightRow.x][rightRow.y])) {

            results.push_back(board[rightRow.x][rightRow.y]);
            if (rook.tileOccupiedByEnemy(board[rightRow.x][rightRow.y])) {
                break;
            }
            rightRow.x++;
        }

        return results;
    }

    std::vector<Tile*> MoveLogic::getKnightPossibleMovePtrs(const Piece& knight, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile*> results;
        sf::Vector2i currentPosition = knight.tilePtr->boardPosition;

        std::array<int, 8> xShifts = { -2, -2, -1, -1, 1,  1, 2,  2 };
        std::array<int, 8> yShifts = {  1, -1,  2, -2, 2, -2, 1, -1 };
        for (int i = 0; i < 8; i++) {
            sf::Vector2i checkPosition(currentPosition.x + xShifts[i], currentPosition.y + yShifts[i]);
            if (checkPosition.x >= 0 && checkPosition.x <= 7 && checkPosition.y >= 0
                && checkPosition.y <= 7 && !knight.tileOccupiedByFriendly(board[checkPosition.x][checkPosition.y])) {
                results.push_back(board[checkPosition.x][checkPosition.y]);
            }
        }

        return results;
    }

    std::vector<Tile*> MoveLogic::getBishopPossibleMovePtrs(const Piece& bishop, const std::array<std::array<Tile*, 8>, 8>& board)
    {
        std::vector<Tile*> results;
        sf::Vector2i currentPosition = bishop.tilePtr->boardPosition;

        sf::Vector2i leftUpDiagonal(currentPosition.x - 1, currentPosition.y - 1);
        while (isInside(leftUpDiagonal) && !bishop.tileOccupiedByFriendly(board[leftUpDiagonal.x][leftUpDiagonal.y])) {

            results.push_back(board[leftUpDiagonal.x][leftUpDiagonal.y]);
            if (bishop.tileOccupiedByEnemy(board[leftUpDiagonal.x][leftUpDiagonal.y])) {
                break;
            }
            leftUpDiagonal.x--;
            leftUpDiagonal.y--;
        }

        sf::Vector2i rightDownDiagonal(currentPosition.x + 1, currentPosition.y + 1);
        while (isInside(rightDownDiagonal) && !bishop.tileOccupiedByFriendly(board[rightDownDiagonal.x][rightDownDiagonal.y])) {

            results.push_back(board[rightDownDiagonal.x][rightDownDiagonal.y]);
            if (bishop.tileOccupiedByEnemy(board[rightDownDiagonal.x][rightDownDiagonal.y])) {
                break;
            }
            rightDownDiagonal.x++;
            rightDownDiagonal.y++;
        }

        sf::Vector2i leftDownDiagonal(currentPosition.x - 1, currentPosition.y + 1);
        while (isInside(leftDownDiagonal) && !bishop.tileOccupiedByFriendly(board[leftDownDiagonal.x][leftDownDiagonal.y])) {

            results.push_back(board[leftDownDiagonal.x][leftDownDiagonal.y]);
            if (bishop.tileOccupiedByEnemy(board[leftDownDiagonal.x][leftDownDiagonal.y])) {
                break;
            }
            leftDownDiagonal.x--;
            leftDownDiagonal.y++;
        }

        sf::Vector2i rightUpDiagonal(currentPosition.x + 1, currentPosition.y - 1);
        while (isInside(rightUpDiagonal) && !bishop.tileOccupiedByFriendly(board[rightUpDiagonal.x][rightUpDiagonal.y])) {

            results.push_back(board[rightUpDiagonal.x][rightUpDiagonal.y]);
            if (bishop.tileOccupiedByEnemy(board[rightUpDiagonal.x][rightUpDiagonal.y])) {
                break;
            }
            rightUpDiagonal.x++;
            rightUpDiagonal.y--;
        }

        return results;
    }

    std::vector<Tile*> MoveLogic::getQueenPossibleMovePtrs(const Piece& queen, const std::array<std::array<Tile*, 8>, 8>& board) {
        std::vector<Tile *> bishopAndRookResults = getBishopPossibleMovePtrs(queen, board);
        std::vector<Tile *> rookResults = getRookPossibleMovePtrs(queen, board);

        bishopAndRookResults.insert(bishopAndRookResults.end(), rookResults.begin(), rookResults.end());
        return bishopAndRookResults;
    }

}