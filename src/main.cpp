#include <SFML/Graphics.hpp>
#include <board.hpp>
#include <iostream>
#include <piece.hpp>

const sf::Vector2f windowDimensions(800, 800);

void deselectPiece(Chess::Piece& piece, Chess::Board& board) {
    piece.tilePtr->shape.setFillColor(piece.tilePtr->getNormalColor());
    //std::cout << piece.getValidMoveTilesPtrs(board.board).size();
    //for (auto tile : piece.getValidMoveTilesPtrs(board.board)) {
        // if (tile) {
        //     auto& validTile = *tile;
        //     validTile.shape.setFillColor(validTile.getNormalColor());
        // }
        //tile.get().shape.setFillColor(tile.get().getNormalColor());
    //}        
    
    for (auto tile : piece.getValidMoveTiles(board.board)) {
        tile.get().shape.setFillColor(tile.get().getNormalColor());
    }
}

void selectPiece(Chess::Piece& selectedPieceRef, Chess::Board& board) {
    selectedPieceRef.tilePtr->shape.setFillColor(sf::Color::Green);
    // for (auto tileWrapper : selectedPieceRef.getValidMoveTiles(board.board)) {
    //     tileWrapper.get().shape.setFillColor(sf::Color::Red);
    // }
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

    sf::RenderWindow window(sf::VideoMode(windowDimensions.x, windowDimensions.y),
        "Chess++");

    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("../img/chess-sprites.png")) {
        ;// TODO handle error here (maybe texture.create(200, 200)?)
    }

    Chess::Board board(windowDimensions.x / 8);
    std::vector<Chess::Piece> pieces = board.setPieces(spriteSheet);
    //Chess::Piece * selectedPiecePtr = 0;
    //Chess::Piece& selectedPiece = pieces[0];// = 0;
    //Chess::Piece selectedPiece = 0;
    //for (auto piece : pieces) {
        //std::cout << "Direct piece color: " << piece.color << std::endl;
        //Chess::Tile tile = *piece.tilePtr;
        //std::cout << "Piece position: (" << tile.boardPosition.x << ", " << tile.boardPosition.y << ")" << std::endl;
    //}
    //Chess::Piece & piece2 = *(board.board[7][1].piecePtr);
    //Chess::Piece piece = board.board[0][1].piecePtr;
    //std::cout << "Outside (0, 0) type (method 1): " << piece.pieceType << std::endl;// Always 5

    //std::cout << "Outside (0, 1) type (method 2): " << ((board.board)[0][1].piecePtr->pieceType) << std::endl; // Wrong for (0, 1)
    
    // for (auto& piece : pieces) {
    //     Chess::Tile tile = *piece.tilePtr;
    //     std::cout << "Piece type " << piece.pieceType << " at (" << tile.boardPosition.x << ", " << tile.boardPosition.y << ")" << std::endl;
    // } 
    /*
    for (auto& row : board.board) {
        for (auto& tile : row) {
            
            if (false && tile.piecePtr) {
                
                // TODO : Why do these 3 methods have different behavior?
                Chess::Piece piece = *tile.piecePtr;
                std::cout << "Color (unwrapped ptr): " << piece.color << std::endl;
                std::cout << "Other method: " << (*tile.piecePtr).color << std::endl;
                std::cout << "Method 3: " << tile.piecePtr->color << std::endl;
                //std::cout << "Color: " << tile.piecePtr->color << std::endl;
                
            }
        }
    }*/

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
                    
                    for (auto tileCoords : pieces[selectedPieceIndex].getValidMoveCoordinates(board.board)) {
                        auto& validMoveTile = board.board[tileCoords.x][tileCoords.y];
                        if (validMoveTile.shape.getGlobalBounds().contains(mouseCoords)) {
                            clearBoardHighlights(board);
                            pieces[selectedPieceIndex].moveToTile(validMoveTile);
                            selectedPieceIndex = -1;
                        } 
                    }
                } else {
                    for (int i = 0; i < pieces.size(); ++i) {
                        
                        if (pieces[i].sprite.getGlobalBounds().contains(mouseCoords)) {
                            // Clear board highlights
                            clearBoardHighlights(board);
                            selectedPieceIndex = i;
                            // TODO maybe check that this tilePtr exists
                            pieces[selectedPieceIndex].tilePtr->shape.setFillColor(sf::Color::Green);
                            //std::cout << "here";
                            for (auto tileCoords : pieces[selectedPieceIndex].getValidMoveCoordinates(board.board)) {
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
            window.draw(piece.sprite);
        }
        window.display();
    }

    return 0;
}
