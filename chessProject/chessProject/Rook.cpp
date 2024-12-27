#include "Rook.h"


Rook::Rook(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if the piece is white (white == got rights)
	{
		this->_sign = WhiteRook; // setting the sign to a white rook
	}
	else // piece is black (black == no rights)
	{
		this->_sign = BlackRook; // set the sign to a black rook
	}
}

MoveResult Rook::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
{

	auto dstInPathResult = isDstInPath(dst); // store the returned tuple
	// extract the values
	bool isInPath;
	Direction direction;
	std::tie(isInPath, direction) = dstInPathResult;

	if (!isInPath) // if the destination is not in path
	{
		return IllegalPieceMove;
	}

	// check if there are pieces in the way that disallows the piece to move there
	if (arePiecesInWay(board, direction, dst))
	{
		return IllegalPieceMove;
	}

	return Legal;
}


bool Rook::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
	Coord currentCoord = calcDst(this->_coord, 1, direction); // save the next piece
	while (!currentCoord.isEqual(dst)) // while we havent reached the destination yet
	{
		if (board[currentCoord.Row][currentCoord.Col] != NULL)
		{
			return true; // piece are in the way
		}
		currentCoord = calcDst(currentCoord, 1, direction); // go to the next coord
	}
	return false;
}

std::tuple<bool, Direction> Rook::isDstInPath(Coord dst)
{
	if (!isStraightLine(this->_coord, dst)) // if the movement is not in a direct line
	{
		return std::make_tuple(false, None); // return false and garbage char
	}
	return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction
}