#pragma once
#include "piece.h"
#include "board.h"

class Piece;
class Board;

class Rook : public Piece
{
public:
	Rook(std::string location, bool isBlack, Board& const board);
	~Rook();

	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};