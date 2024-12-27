#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(Coord coord, Color color);
	virtual MoveResult checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS]) override;

private:
	virtual bool arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst) override;
	virtual std::tuple<bool, Direction> isDstInPath(Coord dst) override;
};