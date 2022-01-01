#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>
#include "piece.h"
#include "main.h"

void highlightPossibleMoves(Chess::Board& board, Chess::Piece*& selectedPiece) {
    board.resetColors();
    selectedPiece->tilePtr->shape.setFillColor(sf::Color::Green);
    for (auto& tile : selectedPiece->getValidMoveTilePtrs(board.board)) {
        tile->shape.setFillColor(sf::Color::Red);
    }
}

void handleMouseClick(Chess::Piece*& selectedPiece, Chess::Board& board, const sf::Vector2f mouseCoords) {
    // If a piece was already selected, check if one of its move options was clicked
    // If so, move it to that tile
    // Else, check if a piece was clicked, and if one was, make it the selected piece
    if (selectedPiece) {
        for (auto& tilePtr : selectedPiece->getValidMoveTilePtrs(board.board)) {
            if (tilePtr->shape.getGlobalBounds().contains(mouseCoords)) {
                board.resetColors();
                board.movePieceToTile(selectedPiece, tilePtr);
                selectedPiece = nullptr;
            }
        }
    }
    for (auto& piece : board.pieces) {
        if (piece->sprite.getGlobalBounds().contains(mouseCoords)) {
            selectedPiece = piece;
            highlightPossibleMoves(board, selectedPiece);
        }
    }
}

int main() {

    const sf::Vector2f windowDimensions(800, 800);
    sf::RenderWindow window(sf::VideoMode((unsigned int) windowDimensions.x, (unsigned int) windowDimensions.y),
        "Chess++");
        
    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("chess-sprites.png")) {
        // Make sure Visual Studio is set to the correct Debug/Release Settings
        // If VS is in Debug mode, all libraries should have SFML-xyz-d.lib
        // else, they should just have SFML-xyz.lib
        std::cout << "Failed to load sprite sheet\n";
        return 1;
    }


    Chess::Board board(windowDimensions.x / 8);
    board.setPieces(spriteSheet);    
    Chess::Piece* selectedPiece = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                handleMouseClick(selectedPiece, board, mouseCoords);

            }
        }
        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
