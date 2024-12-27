#include "Queen.h"

Queen::Queen(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if its a white piece (white == got rights)
	{
		this->_sign = WhiteQueen; // setting the sign to a white queen
	}
	else // its a black piece (black == no rights)
	{
		this->_sign = BlackQueen; // setting the sign to a black queen
	}
}

MoveResult Queen::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
{
	auto dstInPathResult = isDstInPath(dst); // store the returned tuple
	// extract the values
	bool isInPath;
	Direction direction;
	std::tie(isInPath, direction) = dstInPathResult;

	if (!isInPath) // if the destination is not in path
	{
		return IllegalPieceMove; // return illegal piece move
	}

	// check if there are pieces in the way that disallows the piece to move there
	if (arePiecesInWay(board, direction, dst))
	{
		return IllegalPieceMove;
	}
	return Legal;
}

bool Queen::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
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
	return false; // no pieces in the way
}

std::tuple<bool, Direction> Queen::isDstInPath(Coord dst)
{
	// if the move is not straight and not diagonal
	if (!isStraightLine(this->_coord, dst) && !isDiagonalLine(this->_coord, dst))
	{
		return std::make_tuple(false, None); // return false and garbage char
	}
	return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction
}