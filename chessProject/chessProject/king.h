#pragma once
#include "piece.h"

class Piece;
class Board;

class King : public Piece {
public:
	King(std::string location, bool isBlack);
	~King();

	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};