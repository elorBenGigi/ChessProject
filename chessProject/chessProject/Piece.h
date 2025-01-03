#pragma once
#include "coord.h"
#include <exception>
#include <tuple>

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS


enum Sign
{
	// black pieces
	BlackRook = 'r',
	BlackKnight = 'n',
	BlackBishop = 'b',
	BlackKing = 'k',
	BlackQueen = 'q',
	BlackPawn = 'p',

	// white pieces
	WhiteRook = 'R',
	WhiteKnight = 'N',
	WhiteBishop = 'B',
	WhiteKing = 'K',
	WhiteQueen = 'Q',
	WhitePawn = 'P',

	EmptySquare = '#',
};

enum Color
{
	WHITE_PIECE = 0,
	BLACK_PIECE = 1,
};




enum MoveResult
{
	NoResult = '-',

	// legal moves
	Legal = '0',
	LegalCheck = '1',

	// illegal moves
	NoPieceOnSourceSquare = '2',
	OwnPieceOnTargetSquare = '3',
	SelfCheck = '4',
	InvalidSquareIndexes = '5',
	IllegalPieceMove = '6',
	SourceAndTargetSquaresEqual = '7',

	// checkmate
	CheckMate = '8',

};

enum Direction
{
	None = -1,

	UP = 0,
	DOWN,
	LEFT,
	RIGHT,

	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
};

class Piece
{
protected:
	Coord _coord;
	Color _color;
	Sign _sign;

	bool isStraightLine(Coord coord1, Coord coord2);
	bool isDiagonalLine(Coord coord1, Coord coord2);
	std::tuple<int, int> calcUnsignedDelta(Coord coord1, Coord coord2);
	std::tuple<int, int> calcSignedDelta(Coord coord1, Coord coord2);
	virtual bool arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst) = 0;
	virtual std::tuple<bool, Direction> isDstInPath(Coord dst) = 0;
	Direction getDirection(Coord src, Coord dst);

public:
	Piece(Coord coord, Color color);
	virtual MoveResult checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS]) = 0;
	static Coord calcDst(Coord src, int numOfSteps, Direction direction);
	void setCoord(Coord coord);
	Coord getCoord() const;
	Color getColor() const;
	Sign getSign() const;
};