#include "Bishop.h"

Bishop::Bishop(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if its a white piece (white == got rights)
	{
		this->_sign = WhiteBishop; // setting the sign to a white bishop
	}
	else // its a black piece (black == no rights)
	{
		this->_sign = BlackBishop; // setting the sign to a black bishop
	}
}

MoveResult Bishop::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
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

bool Bishop::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
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
	return false; // there are no pieces in the way
}

std::tuple<bool, Direction> Bishop::isDstInPath(Coord dst)
{
	if (!isDiagonalLine(this->_coord, dst)) // if its not a diagonal line
	{
		return std::make_tuple(false, None); // return false and garbage char
	}
	return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction
}