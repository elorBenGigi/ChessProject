#include "rook.h"

Rook::Rook(std::string location, bool isBlack, Board& const board) : Piece(location, isBlack, board) {

}

Rook::~Rook() {
}

bool Rook::isMoveValidPiece(std::string move)
{
	int stepsSideways = handle::moveSideways(move);
	int stepsForwardOrBackward = handle::moveBackOrForward(move);
	if (this->pieceType() == BLACK_ROOK) {
		return Board::isKingAttacked(_board.getKing(false));
	}
	if (this->pieceType() == WHITE_ROOK) {
		return Board::isKingAttacked(_board.getKing(true));
	}
		

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
	if (isBlack())
	{
		return BLACK_ROOK;
	}
	else
	{
		return WHITE_ROOK;
	}
}