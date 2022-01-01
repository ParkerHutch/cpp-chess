#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>
#include "piece.h"

const sf::Vector2f windowDimensions(800, 800);

void deselectPiece(Chess::Piece& piece, Chess::Board& board) {
    piece.tilePtr->shape.setFillColor(piece.tilePtr->getNormalColor());      

    for (auto tile : piece.getValidMoveTiles(board.board)) {
        tile.get().shape.setFillColor(tile.get().getNormalColor());
    }
}

void selectPiece(Chess::Piece& selectedPieceRef, Chess::Board& board) {
    selectedPieceRef.tilePtr->shape.setFillColor(sf::Color::Green);
    
    for (auto tileCoords : selectedPieceRef.getValidMoveCoordinates(board.board)) {
        board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
    }
}

void clearBoardHighlights(Chess::Board& board) {
    for (auto& row : board.board) {
        for (auto& tile : row) {
            tile.shape.setFillColor(tile.getNormalColor());
        }
    }
}

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
    std::vector<Chess::Piece *> pieces = board.setPieces(spriteSheet); // TODO this should probably be a variable stored in the board
    

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (selectedPieceIndex != -1) {
                    // If a piece is selected, check if one of its move options was clicked
                    // If so, move it to that tile

                    for (auto tileCoords : pieces[selectedPieceIndex]->getValidMoveCoordinates(board.board)) {
                        auto& validMoveTile = board.board[tileCoords.x][tileCoords.y];
                        if (validMoveTile.shape.getGlobalBounds().contains(mouseCoords)) {
                            
                            clearBoardHighlights(board); // TODO this should probably be a board method
                            
                            board.movePieceToTile(validMoveTile, *pieces[selectedPieceIndex], pieces);
                            
                            selectedPieceIndex = -1;
                        }
                    }
                }
                else {
                    for (int i = 0; i < pieces.size(); ++i) {
                        
                        if (pieces[i]->sprite.getGlobalBounds().contains(mouseCoords)) {
                            // Clear board highlights
                            clearBoardHighlights(board);
                            selectedPieceIndex = i;
                            // TODO maybe check that this tilePtr exists
                            pieces[selectedPieceIndex]->tilePtr->shape.setFillColor(sf::Color::Green);
                            //std::cout << "here";
                            for (auto tileCoords : pieces[selectedPieceIndex]->getValidMoveCoordinates(board.board)) {
                                //std::cout << "executing line" << std::endl;
                                board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
                            }

                        }
                    }
                }

            }
        }
        window.clear();

        // Draw the chess board
        for (auto row : board.board) {
            for (auto tile : row) {
                window.draw(tile.shape);
            }
        }
        // Draw the pieces
        for (auto piece : pieces) {
            
            window.draw(piece->sprite);
            
        }
        window.display();
    }

    return 0;
}
