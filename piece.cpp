#include <vector>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "tile.h"
#include "board.h"
#include <functional>
#include <iostream>
#include <array>
#include "MoveLogic.h"

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

    bool Piece::tileOccupiedByEnemy(const Tile * tilePtr) const {
        return tilePtr->piecePtr ? tilePtr->piecePtr->color != this->color : false;
    }

}