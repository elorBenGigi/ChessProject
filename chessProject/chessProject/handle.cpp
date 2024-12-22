#include "handle.h"

handle::handle() {
}

handle::~handle() {
}

// checking if the move is sideways
int handle::moveSideways(std::string move)
{
	if (move[DEST_ROW] == move[SRC_ROW])
	{
		return move[DEST_COL] - move[SRC_COL];
	}
	return 0;

}

// checking if the move is forwards or backwards
int handle::moveBackOrForward(std::string move)
{
	if (move[DEST_COL] == move[SRC_COL])
	{
		return move[DEST_ROW] - move[SRC_ROW];
	}
	return 0;
}

// checking if the move is a diagonal move
int handle::moveDiagonally(std::string move)
{
	int stepCounter = 0;
	int deltaX = move[DEST_COL] - move[SRC_COL];
	int deltaY = move[DEST_ROW] - move[SRC_ROW];

	if (1 == abs(double(deltaX) / deltaY)) // convert the double to increase accuracy
	{
		stepCounter = deltaY;
	}
	return stepCounter;
}

// checking if a move is only one square long
bool handle::singleMove(std::string move)
{
	int side = moveSideways(move);
	int forward = moveBackOrForward(move);
	int diagonal = moveDiagonally(move);

	// if the move is not a single one, and isnt a diagonal, backwards, forwards or sideways move
	if (((abs(side) > 1) || (abs(forward) > 1) || (abs(diagonal) > 1) || ((0 == forward) && (0 == side) && (0 == diagonal))))
	{
		return false;
	}

	return true;
}