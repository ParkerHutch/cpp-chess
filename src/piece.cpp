#include <vector>
#include <SFML/Graphics.hpp>
#include <piece.hpp>
#include <tile.hpp>
#include <iostream>

namespace Chess {

    Piece::Piece(bool color) {
        this->color = color;
        this->tilePtr = 0;
        this->pieceType = PAWN;
    } 
    
    Piece::Piece(Tile& tile, bool color, const int pieceType) {
        this->color = color;
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->pieceType = pieceType;
        //loadSprite(spriteSheet);
    }

    Piece::Piece(Tile& tile, bool color, const int pieceType, const sf::Texture& spriteSheet) {
        this->color = color;
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->pieceType = pieceType;
        //std::cout << "before load";
        loadSprite(spriteSheet);
        this->sprite.setPosition(tile.shape.getPosition());
        //std::cout << " after load!" << std::endl;
    }

    int spriteTextureWidth = 45;
    int spriteTextureHeight = 45;
    void Piece::loadSprite(const sf::Texture& spriteSheet) {
        int leftX = pieceType * spriteTextureWidth;
        int topY = color * spriteTextureHeight;
        this->sprite.setTexture(spriteSheet);
        this->sprite.setTextureRect(sf::IntRect(leftX, topY, 
                                    spriteTextureWidth, spriteTextureHeight));
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