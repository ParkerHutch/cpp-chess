#include <vector>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "tile.h"
#include <functional>
#include <iostream>
#include <array>

namespace Chess {

    Piece::Piece(bool color) {
        this->color = color;
        this->tilePtr = 0;
        this->pieceType = PAWN;
    }

    Piece::Piece(Tile& tile, int color, const int pieceType) {
        this->color = color;
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->pieceType = pieceType;
    }

    Piece::Piece(Tile& tile, int color, const int pieceType, const sf::Texture& spriteSheet) {
        this->color = color;
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->pieceType = pieceType;
        loadSprite(spriteSheet);
        this->sprite.setPosition(tile.shape.getPosition());
    }

    void Piece::moveToTile(Tile& tile) {
        this->tilePtr->piecePtr = nullptr;
        this->tilePtr->shape.setFillColor(this->tilePtr->getNormalColor());
        
        if (tile.piecePtr != nullptr) {
            // TODO should delete the piece ptr here to make sure memory isn't getting leaked (I think?)
            //delete tile.piecePtr;
        }
        
        tile.piecePtr = this;
        this->tilePtr = &tile;
        this->sprite.setPosition(tile.shape.getPosition());
    }

    int spriteTextureWidth = 45; // TODO declare these somewhere else
    int spriteTextureHeight = 45;
    void Piece::loadSprite(const sf::Texture& spriteSheet) {
        int leftX = pieceType * spriteTextureWidth;
        int topY = color * spriteTextureHeight;
        this->sprite.setTexture(spriteSheet);
        this->sprite.setTextureRect(sf::IntRect(leftX, topY,
            spriteTextureWidth, spriteTextureHeight));
    }

    bool Piece::boardPositionOccupied(sf::Vector2i position, std::array<std::array<Tile, 8>, 8>& board) {

        return board[position.x][position.y].piecePtr != nullptr;
    }

    bool Piece::boardPositionOccupiedByEnemy(const sf::Vector2i position, const std::array<std::array<Tile, 8>, 8>& board) {
        auto& tile = board[position.x][position.y];
        return tile.piecePtr ? tile.piecePtr->color != this->color : false;
    }

    // TODO test this version
    std::vector<Tile*> Piece::getValidMoveTilesPtrs(std::array<std::array<Tile, 8>, 8>& board) {
        std::vector<Tile*> results;
        if (!(this->tilePtr)) {
            std::cout << "ending early, this is bad" << std::endl;
            return results;
        }
        sf::Vector2i currentPosition = this->tilePtr->boardPosition;

        switch (this->pieceType) {
        case PAWN:
        {
            if (this->color == WHITE) {
                sf::Vector2i forwardsPosition(currentPosition.x, currentPosition.y + 1);

                if (forwardsPosition.y <= 7) {

                    if (currentPosition.x > 0) {
                        //std::cout << "here";
                        sf::Vector2i leftDiagonalPosition(currentPosition.x - 1, forwardsPosition.y);
                        // std::cout << "here"; This executes only if this line is present... why?
                        if (boardPositionOccupiedByEnemy(leftDiagonalPosition, board)) {
                            Tile* leftDiagonalTile = &board[leftDiagonalPosition.x][leftDiagonalPosition.y];
                            results.push_back(leftDiagonalTile);
                        }
                    }
                    if (currentPosition.x <= 6) {
                        sf::Vector2i rightDiagonalPosition(currentPosition.x + 1, forwardsPosition.y);

                        if (boardPositionOccupiedByEnemy(rightDiagonalPosition, board)) {
                            Tile* rightDiagonalTile = &board[rightDiagonalPosition.x][rightDiagonalPosition.y];
                            results.push_back(rightDiagonalTile);
                        }
                    }
                    if (!boardPositionOccupied(forwardsPosition, board)) {
                        Tile* forwardsTile = &board[forwardsPosition.x][forwardsPosition.y];
                        results.push_back(forwardsTile);
                    }

                }
            }
            else {
                sf::Vector2i forwardsPosition(currentPosition.x, currentPosition.y + -1);

                if (forwardsPosition.y >= 0) {
                    if (!boardPositionOccupied(forwardsPosition, board)) {
                        Tile* forwardsTile = &board[forwardsPosition.x][forwardsPosition.y];
                        results.push_back(forwardsTile);
                    }

                    if (currentPosition.x > 0) {
                        sf::Vector2i leftDiagonalPosition(currentPosition.x - 1, forwardsPosition.y);

                        if (boardPositionOccupiedByEnemy(leftDiagonalPosition, board)) {
                            Tile* leftDiagonalTile = &board[leftDiagonalPosition.x][leftDiagonalPosition.y];
                            results.push_back(leftDiagonalTile);
                        }
                    }
                    if (currentPosition.x + 1 < 8) {
                        sf::Vector2i rightDiagonalPosition(currentPosition.x + 1, forwardsPosition.y);

                        if (boardPositionOccupiedByEnemy(rightDiagonalPosition, board)) {
                            Tile* rightDiagonalTile = &board[rightDiagonalPosition.x][rightDiagonalPosition.y];
                            results.push_back(rightDiagonalTile);
                        }
                    }
                }
            }
        }
        break;

        default:
            break;
        }
        return results;
    }

    std::vector<std::reference_wrapper<Tile>> Piece::getValidMoveTiles(std::array<std::array<Tile, 8>, 8>& board) {
        std::vector<std::reference_wrapper<Tile>> results;
        if (!(this->tilePtr)) {
            return results;
        }
        sf::Vector2i currentPosition = this->tilePtr->boardPosition;

        switch (this->pieceType) {
        case PAWN:
        {
            sf::Vector2i forwardsPosition(currentPosition.x, currentPosition.y + 1 - 2 * this->color);
            Tile& forwardsTile = board[forwardsPosition.x][forwardsPosition.y];
            if (forwardsPosition.y >= 0 && forwardsPosition.y <= 7 && !boardPositionOccupied(forwardsPosition, board)) {
                results.push_back(forwardsTile);
            }

            if (currentPosition.x - 1 > 0) {
                sf::Vector2i leftDiagonalPosition(currentPosition.x - 1, currentPosition.y + 1 - 2 * this->color);
                Tile& leftDiagonalTile = board[leftDiagonalPosition.x][leftDiagonalPosition.y];

                if (boardPositionOccupiedByEnemy(leftDiagonalPosition, board)) {
                    results.push_back(leftDiagonalTile);
                }
            }
            if (currentPosition.x + 1 < 8) {
                sf::Vector2i rightDiagonalPosition(currentPosition.x + 1, currentPosition.y + 1 - 2 * this->color);
                Tile& rightDiagonalTile = board[rightDiagonalPosition.x][rightDiagonalPosition.y];

                if (boardPositionOccupiedByEnemy(rightDiagonalPosition, board)) {
                    results.push_back(rightDiagonalTile);
                }
            }
        }
        break;

        default:
            break;
        }
        return results;
    }

    std::vector<sf::Vector2i> Piece::getValidMoveCoordinates(std::array<std::array<Tile, 8>, 8>& board) {
        std::vector<sf::Vector2i> results;
        if (!(this->tilePtr)) {
            std::cout << "The selected piece has no tile pointer, exiting\n";
            return results;
        }
        sf::Vector2i currentPosition = this->tilePtr->boardPosition;
        switch (this->pieceType) {
        case PAWN:
        {
            std::cout << "Selected piece color: " << this->color << "\n";
            sf::Vector2i forwards(currentPosition.x, currentPosition.y + 1 - 2 * this->color);
            /*
            
            if (forwards.y >= 0 && forwards.y <= 7) {
                if (!boardPositionOccupied(forwards, board)) {
                    results.push_back(forwards);
                }
                else {
                    results.push_back(forwards);
                }
            }
            else {
                std::cout << "Next spot is out of bounds\n";
            }
            */
            
            if (forwards.y >= 0 && forwards.y <= 7) {
                if (!boardPositionOccupied(forwards, board)) {
                    results.push_back(forwards);
                }
                if (currentPosition.x > 0) {
                    sf::Vector2i leftDiagonal(currentPosition.x - 1, currentPosition.y + 1 - 2 * this->color);
                    if (board[leftDiagonal.x][leftDiagonal.y].piecePtr) { // TODO need to make sure it's an enemy as well
                        //Piece leftDiagonalPiece = *board[leftDiagonal.x][leftDiagonal.y].piecePtr;
                        Piece * leftDiagonalPiece = board[leftDiagonal.x][leftDiagonal.y].piecePtr;
                        //std::cout << "leftDiagonalPiece color: " << leftDiagonalPiece.color << "\n";
                        std::cout << "left diagonal piece color: " << leftDiagonalPiece->color << "\n";
                        /*
                        if (leftDiagonalPiece.color != this->color) {
                            results.push_back(leftDiagonal);
                            std::cout << "Left diagonal color: " << leftDiagonal
                        }
                        */
                        results.push_back(leftDiagonal);
                        
                    }
                }
                
                if (currentPosition.x <= 6) {
                    sf::Vector2i rightDiagonal(currentPosition.x + 1, currentPosition.y + 1 - 2 * this->color);
                    if (board[rightDiagonal.x][rightDiagonal.y].piecePtr) { // TODO need to make sure it's an enemy as well
                        Piece * rightDiagonalPiece = board[rightDiagonal.x][rightDiagonal.y].piecePtr;
                        std::cout << "right diagonal piece color: " << rightDiagonalPiece->color << "\n";

                        if (rightDiagonalPiece->color != this->color) {
                            
                            
                            results.push_back(rightDiagonal);
                        }
                        else {

                            std::cout << "right diagonal has the same color\n";
                        }
                        
                    }
                    
                }
            }
            
        }
        break;

        default:
            std::cout << "Selected piece has no type so default case is happening, bad\n";
            break;
        }
        return results;
    }

    /*
    std::vector<sf::Vector2f> Piece::getMovePositions() {
        switch (this->pieceType) {
            case PAWN:
                // Code
                break;

            default:
                break;
        }
    }
    */
}