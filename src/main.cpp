#include <SFML/Graphics.hpp>
#include <board.hpp>
#include <iostream>
#include <piece.hpp>

const sf::Vector2f windowDimensions(800, 800);

void deselectPiece(Chess::Piece& piece, Chess::Board& board) {
    piece.tilePtr->shape.setFillColor(piece.tilePtr->getNormalColor());
    for (auto tileCoords : piece.getValidMoveCoordinates(board.board)) {
        // De-highlight the old move tiles
        board.board[tileCoords.x][tileCoords.y].shape.setFillColor(board.board[tileCoords.x][tileCoords.y].getNormalColor());
    }
}

void selectPiece(Chess::Piece& selectedPieceRef, Chess::Board& board) {
    selectedPieceRef.tilePtr->shape.setFillColor(sf::Color::Green);
    for (auto tileCoords : selectedPieceRef.getValidMoveCoordinates(board.board)) {
        board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
    }
}

int main() {
    int selectedPieceIndex = -1;

    sf::RenderWindow window(sf::VideoMode(windowDimensions.x, windowDimensions.y),
        "Chess++");

    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("../img/chess-sprites.png")) {
        ;// TODO handle error here (maybe texture.create(200, 200)?)
    }

    Chess::Board board(windowDimensions.x / 8);
    std::vector<Chess::Piece> pieces = board.setPieces(spriteSheet);
    Chess::Piece * selectedPiecePtr = 0;
    //Chess::Piece& selectedPiece = pieces[0];// = 0;
    //Chess::Piece selectedPiece = 0;
    
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                if (selectedPieceIndex != -1) { // If a piece is selected, check if one of its move options was clicked
                    for (auto tileCoords : pieces[selectedPieceIndex].getValidMoveCoordinates(board.board)) {
                        auto& validMoveTile = board.board[tileCoords.x][tileCoords.y];
                        if (validMoveTile.shape.getGlobalBounds().contains(mouseCoords)) {
                            // A valid move position was clicked, de-highlight the unused options
                            for (auto& unusedMoveCoords : pieces[selectedPieceIndex].getValidMoveCoordinates(board.board)) {
                                auto& unusedMoveTile = board.board[unusedMoveCoords.x][unusedMoveCoords.y];
                                if (&unusedMoveTile != &validMoveTile) {
                                    unusedMoveTile.shape.setFillColor(unusedMoveTile.getNormalColor());
                                }
                            }
                            // Move the piece to the tile and reset the selected piece
                            pieces[selectedPieceIndex].moveToTile(validMoveTile);
                            selectedPieceIndex = -1;
                        } 
                    }
                }

                //for (auto piece : pieces) { TODO what if I did auto& piece : pieces? would selectedPiece work then?
                for (int i = 0; i < pieces.size(); ++i) {
                    if (pieces[i].sprite.getGlobalBounds().contains(mouseCoords)) {
                        if (selectedPieceIndex != -1) {
                            deselectPiece(pieces[selectedPieceIndex], board); 
                        }
                        

                        selectedPieceIndex = i;
                        selectPiece(pieces[selectedPieceIndex], board);

                    } 
                }
                // Check if any pieces contain the mouse position
                // If a piece does, set it as the selected piece, unselect the last one
                // Unhighlight the valid move spaces of the previously selected piece
                // Highlight valid move spaces of the selected piece

                // If a piece was selected and a tile was clicked, check if
                // that tile is one of the piece's valid move positions
                // If it is, let the piece move to that position
            }
        }
        window.clear();

        // Draw the chess board
        
        
        for (auto row : board.board) {
            for (auto tile : row) {
                window.draw(tile.shape);
                
                    // if (tile.piecePtr) {
                    //     window.draw(tile.piecePtr->sprite); //TODO why doesn't this work?
                    // }
                
            }
        }
        for (auto piece : pieces) {
            window.draw(piece.sprite);
        }
        window.display();
    }

    return 0;
}
