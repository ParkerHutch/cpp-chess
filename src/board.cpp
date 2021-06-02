#include <SFML/Graphics.hpp>
#include <board.hpp>
#include <iostream>

namespace Chess {

    Board::Board() {
        for (int rowIndex = 0; rowIndex < board.size(); ++rowIndex) {
            for (int colIndex = 0; colIndex < board[rowIndex].size(); ++colIndex) {
                board[rowIndex][colIndex] = Tile();
            }
        }
    }

    Board::Board(float sideLength) {
        // sideLength: the side length of the entire board (board should be a square)
        float tileSideLength = sideLength / 8;

        for (int rowIndex = 0; rowIndex < board.size(); ++rowIndex) {
            for (int colIndex = 0; colIndex < board[rowIndex].size(); ++colIndex) {
                board[rowIndex][colIndex] = Tile(sideLength, rowIndex, colIndex, sf::Color::White);
                board[rowIndex][colIndex].shape.setPosition(rowIndex * sideLength, colIndex * sideLength);
            }
        }
    }

}