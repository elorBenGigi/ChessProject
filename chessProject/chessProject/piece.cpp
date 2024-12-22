#include "piece.h"
#include "king.h"

Piece::Piece(std::string location, bool isBlack) {
	this->_currLocation = location;
	this->_isBlack = isBlack;
	this->_isAlive = true;
}

Piece::~Piece() {
}

void Piece::setIsAlive(bool isAlive)
{
	this->_isAlive = isAlive;
}

// setting the piece current location to the new location inputted
void Piece::setLocation(std::string location)
{
	if (!(location[SRC_COL] < MIN_INDEX_COL || location[SRC_COL] > MAX_INDEX_COL || location[SRC_ROW] < MIN_INDEX_ROW || location[SRC_ROW] > MAX_INDEX_ROW))
	{
		this->_currLocation = std::string(location);
	}
}

bool Piece::isAlive()
{
	return this->_isAlive;
}

bool Piece::isBlack()
{
	return this->_isBlack;
}

std::string Piece::getCurrLocation()
{
	return this->_currLocation;

}