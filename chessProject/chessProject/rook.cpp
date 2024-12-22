#include "rook.h"

Rook::Rook(std::string location, bool isBlack) : Piece(location, isBlack) {
}

Rook::~Rook() {
}

bool Rook::isMoveValidPiece(std::string move)
{
	int stepsSideways = handle::moveSideways(move);
	int stepsForwardOrBackward = handle::moveBackOrForward(move);

	if ((!stepsSideways && stepsForwardOrBackward) || (stepsSideways && !stepsForwardOrBackward))
	{
		return true;
	}
	else
	{
		return false;
	}
}

char Rook::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_ROOK;
	}
	else
	{
		return WHITE_ROOK;
	}
}