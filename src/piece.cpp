#include <vector>
#include <SFML/Graphics.hpp>
#include <piece.hpp>
#include <tile.hpp>

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

    void Piece::moveToTile(Tile& tile) {
        this->tilePtr->piecePtr = 0;
        //*((*tilePtr).piecePtr) = 0;
        //(*tilePtr).piecePtr = 0;
        //this->tilePtr->piecePtr = 0;
        this->tilePtr = &tile;
        tile.piecePtr = this;
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

    bool boardPositionOccupied(sf::Vector2i position, std::array<std::array<Tile, 8>, 8>& board) {
        return board[position.x][position.y].piecePtr != 0;
    }

    std::vector<sf::Vector2i> Piece::getValidMoveCoordinates(std::array<std::array<Tile, 8>, 8>& board) {
        std::vector<sf::Vector2i> results;
        if (!(this->tilePtr)) {
            return results;
        }
        sf::Vector2i currentPosition = this->tilePtr->boardPosition;
        
        switch (this->pieceType) {
            case PAWN:
                {
                    sf::Vector2i forwards (currentPosition.x, currentPosition.y + 1 - 2 * this->color);
                    if (forwards.y >= 0 && forwards.y <= 7 && !boardPositionOccupied(forwards, board)) {
                        results.push_back(forwards);
                    }
                    if (currentPosition.x - 1 > 0) {
                        sf::Vector2i leftDiagonal (currentPosition.x - 1, currentPosition.y + 1 - 2 * this->color);
                        if (boardPositionOccupied(leftDiagonal, board)) {
                            results.push_back(leftDiagonal);
                        } 
                    }
                    if (currentPosition.x + 1 < 8) {
                        sf::Vector2i rightDiagonal (currentPosition.x + 1, currentPosition.y + 1 - 2 * this->color);
                        if (boardPositionOccupied(rightDiagonal, board)) {
                            results.push_back(rightDiagonal);
                        } 
                    }
                    //results.push_back(forwards);
                }
                break;
            
            default:
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