#pragma once
#include "piece.h"
#include "checkMate.h"

#define BOARD_SIZE 8
#define GET_SRC 2
#define GET_DST 2
#define STARTING_BOARD "r###k##r################################################R###K##R"

class Piece;
class King;
class checkmate;

class Board
{
private:
	std::string _board[BOARD_SIZE];
	std::vector<Piece*> _pieces;
	unsigned int _currPlayer;

public:
	Board();
	Board(const char str[64]);
	~Board();

	void setBoard(char x, char y, char piece);
	void setCurrPlayer(unsigned int newCurrPlayer);
	unsigned int getCurrPlayer();
	std::string* getBoard();
	unsigned int getNumOfPieces();
	std::vector<Piece*> getPieces();
	char getPieceAt(char x, char y);

	CODES isMoveValid(std::string move);
	static Piece* isKingAttacked(King* king);
	void printBoard();
	bool removePiece(std::string location);
	Piece* getPiece(std::string location);
	CODES makeMove(std::string move);
	King* getKing(bool isBlack);
	static King* staticGetKing(bool isBlack, Board const& _boardName);
	bool isBlockingPiece(std::string dst, std::string src, char type);
	char* initialBoardString();
};