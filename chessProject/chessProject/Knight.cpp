#include "Knight.h"

Knight::Knight(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if its a white piece (white == got rights)
	{
		this->_sign = WhiteKnight; // setting the sign to a white knight
	}
	else // its a black piece (black == no rights)
	{
		this->_sign = BlackKnight; // setting the sign to a black knight
	}
}

MoveResult Knight::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
{
	auto dstInPathResult = isDstInPath(dst); // store the returned tuple
	// extract the values
	bool isInPath;
	Direction direction;
	std::tie(isInPath, direction) = dstInPathResult;

	if (!isInPath) // if the destination is not in the path
	{
		return IllegalPieceMove; // return illegal piece move
	}

	// check if there are pieces in the way that disallows the piece to move there
	if (arePiecesInWay(board, direction, dst))
	{
		return IllegalPieceMove; // return illegal piece move
	}
	return Legal;
}

bool Knight::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
	return false; // there is never anything in the knights way (casual ahh sigma)
}

std::tuple<bool, Direction> Knight::isDstInPath(Coord dst)
{

	auto tupleRes = calcUnsignedDelta(this->_coord, dst); // store the returned tuple
	// extract the values
	int deltaRow;
	int deltaCol;
	std::tie(deltaRow, deltaCol) = tupleRes;

	// if its 2 steps and then 1 step or the other way around its a knight move
	if (deltaRow == 2 && deltaCol == 1 || deltaRow == 1 && deltaCol == 2)
	{
		return std::make_tuple(true, None); // return true since there is no need for direction
	}
	return std::make_tuple(false, None); // return false since there is no need for direction 
}