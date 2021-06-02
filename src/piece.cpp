#include <vector>
#include <SFML/Graphics.hpp>
#include <piece.hpp>

namespace Chess {

    Piece::Piece(bool color) {
        this->color = color;
        this->tilePtr = 0;
        this->pieceType = PAWN;
    }

    Piece::Piece(Tile& tile, bool color, const int pieceType, const sf::Texture& spriteSheet) {
        this->color = color;
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->shape = sf::RectangleShape(sf::Vector2f(80, 80));
        this->shape.setFillColor(sf::Color::Red);
        this->shape.setPosition(tile.shape.getPosition());
        this->pieceType = pieceType;
        loadSprite(spriteSheet);
    }

    int spriteTextureWidth = 45;
    int spriteTextureHeight = 45;
    void Piece::loadSprite(const sf::Texture& spriteSheet) {
        int leftX = pieceType * spriteTextureWidth;
        int topY = color * spriteTextureHeight;
        this->sprite.setTexture(spriteSheet); // TODO use sprite.setColor to modify based on team
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