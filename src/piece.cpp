#include <vector>
#include <SFML/Graphics.hpp>
#include <piece.hpp>

namespace Chess {

    Piece::Piece() {
        this->tilePtr = 0;
        this->pieceType = PAWN;
    }

    Piece::Piece(Tile& tile, const int pieceType) {
        loadSprite();
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->shape = sf::RectangleShape(sf::Vector2f(80, 80));
        this->shape.setFillColor(sf::Color::Red);
        this->shape.setPosition(tile.shape.getPosition());
        this->pieceType = pieceType;
    }

    void Piece::loadSprite() {
        // TODO does texture have to be a class variable?
        if (!texture.loadFromFile("img/chess-sprites.png", sf::IntRect(0, 0, 45, 45))) {
            ;// TODO handle error here (maybe texture.create(200, 200)?)
        }
        this->sprite.setTexture(texture); // TODO use sprite.setColor to modify based on team
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