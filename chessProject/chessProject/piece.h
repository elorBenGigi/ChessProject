#pragma once
#include <vector>

#include "handle.h"
#include "board.h"


class Board;

#define SRC_COL  0
#define SRC_ROW 1
#define DEST_COL 2
#define DEST_ROW 3

#define MAX_INDEX_COL 'h'
#define MAX_INDEX_ROW '8'
#define MIN_INDEX_COL 'a'
#define MIN_INDEX_ROW '1'

#define SRC_COL  0
#define SRC_ROW 1
#define DEST_COL 2
#define DEST_ROW 3

enum CODES
{
	VALID_MOVE = '0',
	VALID_MOVE_CHECK = '1',
	NO_PIECE_IN_SRC = '2',
	PIECE_IN_DST = '3',
	SELF_CHECK = '4',
	INVALID_INDEX = '5',
	INVALID_PIECE_MOVE = '6',
	SRC_IS_DST = '7',
	CHECKMATE = '8'
};

enum PIECES_TYPES
{
	WHITE_ROOK = 'R', WHITE_BISHOP = 'B', WHITE_QUEEN = 'Q', WHITE_KING = 'K', WHITE_PAWN = 'P', WHITE_KNIGHT = 'N',
	BLACK_ROOK = 'r', BLACK_BISHOP = 'b', BLACK_QUEEN = 'q', BLACK_KING = 'k', BLACK_PAWN = 'p', BLACK_KNIGHT = 'n',
	EMPTY_CELL = '#'
};

class Piece
{
protected:
	std::string _currLocation;
	bool _isAlive;
	bool _isBlack;
	Board& _board;

public:
	Piece(std::string location, bool isBlack, Board& const board);
	~Piece();

	void setIsAlive(bool isAlive);
	bool isAlive();
	bool isBlack();
	std::string getCurrLocation() const; 

	void setLocation(std::string location);

	virtual bool isMoveValidPiece(std::string move) = 0;
	virtual char pieceType() = 0;
};