#include "piece.h"
#include "king.h"



Piece::Piece(std::string location, bool isBlack, Board& const board) : _board(board)
{
	_currLocation = location;
	_isBlack = isBlack;
	_isAlive = true;
}

Piece::~Piece() {
}

void Piece::setIsAlive(bool isAlive)
{
	_isAlive = isAlive;
}

// setting the piece current location to the new location inputted
void Piece::setLocation(std::string location)
{
	if (!(location[SRC_COL] < MIN_INDEX_COL || location[SRC_COL] > MAX_INDEX_COL || location[SRC_ROW] < MIN_INDEX_ROW || location[SRC_ROW] > MAX_INDEX_ROW))
	{
		_currLocation = std::string(location);
	}
}

bool Piece::isAlive()
{
	return _isAlive;
}

bool Piece::isBlack()
{
	return _isBlack;
}

std::string Piece::getCurrLocation() const
{
	return _currLocation;

}