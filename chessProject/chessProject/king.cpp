#include "king.h"

King::King(std::string location, bool isBlack, Board& const board) : Piece(location, isBlack, board)
{
}

King::~King()
{
}

bool King::isMoveValidPiece(std::string move)
{
	// the king can only move a single step
	return handle::singleMove(move);
}

char King::pieceType()
{
	if (isBlack())
	{
		return BLACK_KING;
	}
	else
	{
		return WHITE_KING;
	}
}