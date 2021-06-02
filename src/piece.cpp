#include <vector>
#include <SFML/Graphics.hpp>
#include <piece.hpp>

namespace Chess {

    Piece::Piece() {
        this->tilePtr = 0;
    }

    Piece::Piece(Tile& tile, const int pieceType) {
        this->tilePtr = &tile;
        tile.piecePtr = this;
        this->shape = sf::RectangleShape(sf::Vector2f(80, 80));
        this->shape.setFillColor(sf::Color::Red);
        this->shape.setPosition(tile.shape.getPosition());
        this->pieceType = pieceType;
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