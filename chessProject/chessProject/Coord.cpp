#include "Coord.h"


#define MIN_COORD_VALUE 0
#define MAX_COORD_VALUE 7

Coord::Coord()
{
	this->Row = -1; // set row
	this->Col = -1; // set col
}

Coord::Coord(int row, int col)
{
	this->Row = row; // set row
	this->Col = col; // set col
}

Coord::Coord(const Coord& other) : Row(other.Row), Col(other.Col)
{
}

bool Coord::isValid()
{
	// check if the coords values are valid (negative or over the limit)
	if (this->Row < MIN_COORD_VALUE || this->Row > MAX_COORD_VALUE || this->Col < MIN_COORD_VALUE || this->Col > MAX_COORD_VALUE)
	{
		return false;
	}
	return true;
}

bool Coord::isEqual(Coord other)
{
	return this->Row == other.Row && this->Col == other.Col; // the values of the two coords are the same
}