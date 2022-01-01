#pragma once

#include "piece.h"
#include "tile.h"

namespace Chess {
	class Tile;

	class MoveLogic {

	private:
        /**
        * @brief Get all valid move locations for the given pawn piece.
        *
        * Returns a list of board coordinates corresponding to valid move locations
        * for the given pawn. This includes the tile in front of the pawn if it is
        * empty and the two diagonal spots in front of the pawn if they are
        * occupied by pieces of the opposite color.
        *
        * @param pawnPtr the pawn to get valid move locations for
        * @param board the board containing chess pieces
        *
        * @return a list of coordinates on the board that the pawn is allowed to
        * move to according to chess rules
        *
        */
		static std::vector<Tile*> getPawnPossibleMovePtrs(const Piece& pawn, const std::array<std::array<Tile*, 8>, 8>& board);

	public:
		static std::vector<Tile*> getValidMoveTilePtrs(const Piece & piece, const std::array<std::array<Tile*, 8>, 8>& board);

	};
}

