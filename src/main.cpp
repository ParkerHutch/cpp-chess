#include <SFML/Graphics.hpp>
#include <board.hpp>

const sf::Vector2f windowDimensions(800, 800);

int main() {
    sf::RenderWindow window(sf::VideoMode(windowDimensions.x, windowDimensions.y),
        "Chess++");

    Chess::Board board(windowDimensions.x / 8);
    auto tilePtr = &(board.board[0][0]);
    Chess::Piece pawn (board.board[0][0], Chess::PAWN);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the chess board
        for (auto row : board.board) {
            for (auto tile : row) {
                window.draw(tile.shape);
                if (tile.piecePtr) {
                    window.draw(tile.piecePtr->shape);
                }
            }
        }
        //window.draw(pawn.shape);
        window.display();
    }

    return 0;
}
