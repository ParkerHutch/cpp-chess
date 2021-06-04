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

void selectPiece(Chess::Piece& selectedPieceRef, const Chess::Piece& clickedPieceRef, Chess::Board& board) {
    selectedPieceRef = clickedPieceRef;
    selectedPieceRef.tilePtr->shape.setFillColor(sf::Color::Green);
    for (auto tileCoords : selectedPieceRef.getValidMoveCoordinates(board.board)) {
        board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowDimensions.x, windowDimensions.y),
        "Chess++");

    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("../img/chess-sprites.png")) {
        ;// TODO handle error here (maybe texture.create(200, 200)?)
    }

    Chess::Board board(windowDimensions.x / 8);
    std::vector<Chess::Piece> pieces = board.setPieces(spriteSheet);
    //auto tilePtr = &(board.board[0][0]);
    //Chess::Piece pawn (board.board[0][0], Chess::WHITE, Chess::PAWN, spriteSheet);
    Chess::Piece * selectedPiecePtr = 0;
    //Chess::Piece& selectedPiece = pieces[0];// = 0;
    Chess::Piece selectedPiece = 0;
    
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                //pieces[0].sprite.setPosition(500, 500);
                sf::Vector2f mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (&selectedPiece) {
                    for (auto tileCoords : selectedPiece.getValidMoveCoordinates(board.board)) {
                        if (board.board[tileCoords.x][tileCoords.y].shape.getGlobalBounds().contains(mouseCoords)) {
                            /*
                            selectedPiece.sprite.setPosition(board.board[tileCoords.x][tileCoords.y].shape.getPosition());
                            selectedPiece.tilePtr = &board.board[tileCoords.x][tileCoords.y];
                            board.board[tileCoords.x][tileCoords.y].piecePtr = &selectedPiece;
                            */
                           selectedPiece.moveToTile(board.board[tileCoords.x][tileCoords.y]);
                            //selectedPiece.sprite.setPosition(sf::Vector2f(500, 500));
                            //if (selectedPiecePtr) {
                                //std::cout << "attempting ptr" << std::endl;
                                //selectedPiecePtr->sprite.setPosition(board.board[tileCoords.x][tileCoords.y].shape.getPosition());
                            //}
                            //selectedPiece.moveToTile(board.board[tileCoords.x][tileCoords.y]);
                            //selectedPiece.
                        }
                    }
                }

                for (auto piece : pieces) {
                    if (piece.sprite.getGlobalBounds().contains(mouseCoords)) {
                        if (&selectedPiece && selectedPiece.tilePtr) {
                            deselectPiece(selectedPiece, board);
                        }
                        
                        //selectPiece(selectedPiece, piece, board); // TODO not sure if this is good practice
                        selectedPiecePtr = &piece;
                        selectedPiece = piece;
                        
                        selectedPiece.tilePtr->shape.setFillColor(sf::Color::Green);
                        for (auto tileCoords : selectedPiece.getValidMoveCoordinates(board.board)) {
                            board.board[tileCoords.x][tileCoords.y].shape.setFillColor(sf::Color::Red);
                        }
                    } 
                }
                // TODO don't loop through all the tiles, just loop through the 
                // tiles that represent valid moves from the currently selected piece
                /*
                for (auto row : board.board) {
                    for (auto tile : row) {
                        if (tile.shape.getGlobalBounds().contains(mouseCoords)) {
                            //std::cout << "tile contains the click";
                        }
                    }
                }*/
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
                /*
                if (tile.piecePtr) {
                    //window.draw(tile.piecePtr->sprite); TODO why doesn't this work?
                }*/
            }
        }
        //pieces[0].sprite.setPosition(sf::Vector2f(400, 400));
        for (auto piece : pieces) {
            window.draw(piece.sprite);
        }
        window.display();
    }

    return 0;
}
