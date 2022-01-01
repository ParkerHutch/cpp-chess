#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>
#include "piece.h"

const sf::Vector2f windowDimensions(800, 800);

int main() {
    int selectedPieceIndex = -1;

    sf::RenderWindow window(sf::VideoMode((unsigned int) windowDimensions.x, (unsigned int) windowDimensions.y),
        "Chess++");
        
    sf::Texture spriteSheet;
    
    if (!spriteSheet.loadFromFile("chess-sprites.png")) {
        // Make sure Visual Studio is set to the correct Debug/Release Settings
        // If VS is in Debug mode, all libraries should have SFML-xyz-d.lib
        // else, they should just have SFML-xyz.lib
        std::cout << "Failed to load sprite sheet\n";
        ;// TODO handle error here (maybe texture.create(200, 200)?)
    }

    Chess::Board board(windowDimensions.x / 8);
    board.setPieces(spriteSheet);    

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (selectedPieceIndex != -1) {
                    // If a piece is selected, check if one of its move options was clicked
                    // If so, move it to that tile

                    for (auto tileCoords : board.pieces[selectedPieceIndex]->getValidMoveCoordinates(board.board)) {
                        auto& validMoveTile = board.board[tileCoords.x][tileCoords.y];
                        if (validMoveTile.shape.getGlobalBounds().contains(mouseCoords)) {
                            
                            board.clearHighlights();

                            board.movePieceToTile(validMoveTile, *board.pieces[selectedPieceIndex], board.pieces);
                            
                            selectedPieceIndex = -1;
                        }
                    }
                } else {
                    for (int i = 0; i < board.pieces.size(); ++i) {
                        
                        if (board.pieces[i]->sprite.getGlobalBounds().contains(mouseCoords)) {
                            board.clearHighlights();

                            selectedPieceIndex = i;
                            // TODO maybe check that this tilePtr exists
                            board.pieces[selectedPieceIndex]->tilePtr->shape.setFillColor(sf::Color::Green);
                            //std::cout << "here";
                            for (auto tileCoords : board.pieces[selectedPieceIndex]->getValidMoveCoordinates(board.board)) {
                                //std::cout << "executing line" << std::endl;
                                board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
                            }

                        }
                    }
                }

            }
        }
        window.clear();

        board.draw(window);
        
        window.display();
    }

    return 0;
}
