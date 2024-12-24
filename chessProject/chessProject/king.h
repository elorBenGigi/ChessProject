#pragma once
#include "piece.h"

class Board;

class King : public Piece {
public:
	King(std::string location, bool isBlack, Board& const board);
	virtual ~King();

	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};