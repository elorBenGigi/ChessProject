#pragma once
#include "piece.h"

class Piece;

class Rook : public Piece
{
public:
	Rook(std::string location, bool isBlack);
	~Rook();

	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};