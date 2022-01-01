#include <vector>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "tile.h"
#include "board.h"
#include <functional>
#include <iostream>
#include <array>

namespace Chess {

    Piece::Piece(const bool color) {
        this->color = color;
        this->tilePtr = 0;
        this->pieceType = PAWN;
    }

    Piece::Piece(Tile * initialTilePtr, const int color, const int pieceType) {
        this->color = color;
        this->tilePtr = initialTilePtr;
        initialTilePtr->piecePtr = this;
        this->pieceType = pieceType;
    }

    Piece::Piece(Tile * initialTilePtr, const int color, const int pieceType, const sf::Texture& spriteSheet) {
        this->color = color;
        this->tilePtr = initialTilePtr;
        initialTilePtr->piecePtr = this;
        this->pieceType = pieceType;
        loadSprite(spriteSheet);
        this->sprite.setPosition(initialTilePtr->shape.getPosition());
    }

    void Piece::moveToTile(Tile * nextTilePtr) {
        // Reset the tile that the piece is currently on to its default state
        this->tilePtr->piecePtr = nullptr;
        this->tilePtr->shape.setFillColor(this->tilePtr->getNormalColor());
        
        // Make the piece and its new tile point to each other in the respective fields
        nextTilePtr->piecePtr = this;
        this->tilePtr = nextTilePtr;

        // Reposition the piece's sprite
        this->sprite.setPosition(nextTilePtr->shape.getPosition());
    }

    void Piece::draw(sf::RenderWindow& window) const {

        window.draw(sprite);

    }

    
    void Piece::loadSprite(const sf::Texture& spriteSheet) {
        int leftX = pieceType * spriteTextureWidth;
        int topY = color * spriteTextureHeight;
        this->sprite.setTexture(spriteSheet);
        this->sprite.setTextureRect(sf::IntRect(leftX, topY,
            spriteTextureWidth, spriteTextureHeight));
    }

    bool Piece::boardPositionOccupied(const sf::Vector2i position, const std::array<std::array<Tile, 8>, 8>& board) const {

        return board[position.x][position.y].piecePtr != nullptr;
    }

    bool Piece::boardPositionOccupiedByEnemy(const sf::Vector2i position, const std::array<std::array<Tile *, 8>, 8>& board) const {
        auto& tile = board[position.x][position.y];
        return tile->piecePtr ? tile->piecePtr->color != this->color : false;
    }

    bool boardPositionOccupiedByEnemy(Piece * piecePtr, const sf::Vector2i position, const std::array<std::array<Tile *, 8>, 8>& board) {
        auto& tile = board[position.x][position.y];
        return tile->piecePtr ? tile->piecePtr->color != piecePtr->color : false;
    }

    std::vector<Tile *> getPawnPossibleMovePtrs(const Piece& pawn, const std::array<std::array<Tile*, 8>, 8>& board) {

        std::vector<Tile *> results;
        sf::Vector2i currentPosition = pawn.tilePtr->boardPosition;

        sf::Vector2i forwards(currentPosition.x, currentPosition.y + 1 - 2 * pawn.color);
        if (forwards.y >= 0 && forwards.y <= 7) {
            if (board[forwards.x][forwards.y]->piecePtr == nullptr) {
                results.push_back(board[forwards.x][forwards.y]);
            }
            if (currentPosition.x > 0) {
                sf::Vector2i leftDiagonal(currentPosition.x - 1, currentPosition.y + 1 - 2 * pawn.color);

                if (pawn.boardPositionOccupiedByEnemy(leftDiagonal, board)) {

                    results.push_back(board[leftDiagonal.x][leftDiagonal.y]);

                }

            }

            if (currentPosition.x <= 6) {
                sf::Vector2i rightDiagonal(currentPosition.x + 1, currentPosition.y + 1 - 2 * pawn.color);
                if (pawn.boardPositionOccupiedByEnemy(rightDiagonal, board)) {

                    results.push_back(board[rightDiagonal.x][rightDiagonal.y]);

                }


            }
        }

        return results;

    }


    std::vector<Tile*> Piece::getValidMoveTilePtrs(const std::array<std::array<Tile*, 8>, 8>& board) const {

        std::vector<Tile *> results;
        sf::Vector2i currentPosition = this->tilePtr->boardPosition;
        switch (this->pieceType) {
        case PAWN:
        {
            results = getPawnPossibleMovePtrs(*this, board);

        }
        break;

        default:
            std::cout << "Selected piece has no type so default case is happening, bad\n";
            break;
        }
        return results;

    }


}