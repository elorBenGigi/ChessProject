#include "checkMate.h"

// checking for a checkmate
CODES checkmate::isCheckmate(Board& const board, const King& otherKing, const Piece& attacker)
{
	if (!&attacker)
	{
		return VALID_MOVE_CHECK;
	}
	std::string kingLocation = otherKing.getCurrLocation(), attackerLocation = attacker.getCurrLocation(), squareBetween = kingLocation, move = "";
	bool isEscapingPath = false, canAttackerBeEated = false, isBlockingPiece = false;
	bool isCheckMate = false;

	// checking if there is a valid move to escape to

	board.setCurrPlayer(!board.getCurrPlayer());

	isEscapingPath =
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + kingLocation[SRC_ROW]) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + kingLocation[SRC_ROW]) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + ((char)(kingLocation[SRC_ROW] + 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + ((char)(kingLocation[SRC_ROW] + 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[SRC_COL] + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[SRC_COL] + ((char)(kingLocation[SRC_ROW] - 1)));

	board.setCurrPlayer(!board.getCurrPlayer());
	std::cout << isEscapingPath << std::endl;
	// checking if the attacker can be eaten

	for (int i = 0; (i < board.getPieces().size()) && !canAttackerBeEated; i++)
	{
		if (NO_PIECE_IN_SRC > board.isMoveValid(board.getPieces()[i]->getCurrLocation() + attackerLocation))
		{
			canAttackerBeEated = true;
		}
	}


	isBlockingPiece = pieceBetween(attackerLocation, kingLocation, board);

	board.setCurrPlayer(!board.getCurrPlayer()); // return the turn to the player

	isCheckMate = ((!isEscapingPath) && (!canAttackerBeEated) && (!isBlockingPiece));


	return isCheckMate ? CHECKMATE : VALID_MOVE_CHECK;


	return !isEscapingPath && !canAttackerBeEated && !pieceBetween(attackerLocation, kingLocation, board) ? CHECKMATE : VALID_MOVE_CHECK;
}

// checking if a piece of the current player can be moved to block the move between the attacking piece to the king
bool checkmate::pieceBetween(std::string src, std::string dst, Board& const board)
{
	Piece* srcPiece = board.getPiece(src), * dstPiece = board.getPiece(dst);
	std::string squareBetween = dst, move = "";
	int colon = src[COL] - dst[COL], row = src[ROW] - dst[ROW];
	bool isBlockingPiece = false;
	char pieceType = srcPiece->pieceType();

	if (pieceType == BLACK_PAWN || pieceType == WHITE_PAWN || pieceType == BLACK_KNIGHT || pieceType == WHITE_KNIGHT)
	{
		return false;
	}

	// setting the change factors to go over the squares between the king and the attacker
	if (colon != 0)
	{
		colon = colon < 0 ? -1 : 1;
	}
	if (row != 0)
	{
		row = row < 0 ? -1 : 1;
	}

	// going over all the squares bewteen the src piece and the dst piece
	while (squareBetween != src)
	{
		squareBetween[ROW] += row;
		squareBetween[COL] += colon;

		if (squareBetween != src)
		{
			// checking if a piece of the current player can be moved to the current square
			for (int i = 0; (i < board.getPieces().size()) && !isBlockingPiece; i++)
			{
				move = board.getPieces()[i]->getCurrLocation() + squareBetween; // a move from the current piece to the current square
				if (NO_PIECE_IN_SRC > board.isMoveValid(move))
				{
					isBlockingPiece = true;
				}
			}
		}
	}
	return isBlockingPiece;
}