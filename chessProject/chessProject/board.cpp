#include "board.h"
#include "rook.h"
#include "king.h"

Board::Board()
{
	this->_currPlayer = 0;
	Piece* p = nullptr;
	std::string currLocation = "";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			this->_board[i] += STARTING_BOARD[i * BOARD_SIZE + j];
		}
	}

	// starting board build up
	// adding 4 rooks
	p = new Rook("a8", true);
	this->_pieces.push_back(p);
	p = new Rook("h8", true);
	this->_pieces.push_back(p);
	p = new Rook("a1", false);
	this->_pieces.push_back(p);
	p = new Rook("h1", false);
	this->_pieces.push_back(p);

	// adding 2 kings and queens
	p = new King("e1", false);
	this->_pieces.push_back(p);
	p = new King("e8", true);
	this->_pieces.push_back(p);
}

Board::~Board()
{
	for (int i = 0; i < this->_pieces.size(); i++)
	{
		delete this->_pieces[i];
	}
}

unsigned int Board::getNumOfPieces()
{
	return this->_pieces.size();
}


std::vector<Piece*> Board::getPieces()
{
	return this->_pieces;
}


std::string* Board::getBoard()
{
	return this->_board;
}

unsigned int Board::getCurrPlayer()
{
	return this->_currPlayer;
}

void Board::setCurrPlayer(unsigned int newCurrPlayer)
{
	this->_currPlayer = newCurrPlayer;
}

// removing a piece from the board + vector after it was eaten
bool Board::removePiece(std::string location)
{
	int len = 0;
	Piece* target = nullptr;
	bool isTargetFound = false;

	target = this->getPiece(location);

	if (target)
	{
		this->setBoard(location[SRC_ROW], location[SRC_COL], EMPTY_CELL); // removing from the board
		target->setIsAlive(false);
		isTargetFound = true;
	}

	return isTargetFound;
}

// assigning a piece on a location on the board
void Board::setBoard(char x, char y, char piece)
{
	this->_board[(int)(BOARD_SIZE - (x - MIN_INDEX_ROW)) - 1][(int)(y - MIN_INDEX_COL)] = piece;
}

// searching for a piece on a current location on the board from the vector
Piece* Board::getPiece(std::string location)
{
	Piece* target = nullptr;
	int len = 0;
	bool isTargetFound = false;

	len = this->_pieces.size();

	// searching for the piece in the pieces vector
	for (int i = 0; (i < len) && !isTargetFound; i++)
	{
		if (this->_pieces[i]->getCurrLocation() == location && this->_pieces[i]->isAlive())
		{
			target = this->_pieces[i];
			isTargetFound = true;
		}
	}
	return target;
}

// checking for checks
Piece* Board::isKingAttacked(King* king)
{
	bool isBlack = king->isBlack();
	std::string dst = king->getCurrLocation();
	Piece* p = nullptr;
	std::string src = "";

	for (int i = 0; i < this->_pieces.size(); i++)
	{
		p = this->_pieces[i];
		src = p->getCurrLocation();

		// checking if whatever piece (p) is threatening the king
		if ((p->isAlive()) && (p->pieceType() != king->pieceType()) && (p->isBlack() != isBlack) && (p->isMoveValidPiece(src + dst)) && (!this->isBlockingPiece(dst, src, p->pieceType())))
		{
			return p;
		}
	}
	return nullptr;
}

CODES Board::isMoveValid(std::string move)
{
	std::string src = move.substr(0, move.length() / GET_SRC);
	std::string dst = move.substr(DEST_COL, move.length() / GET_DST);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);

	King* otherKing = this->getKing(!this->_currPlayer);
	King* currKing = this->getKing(this->_currPlayer);

	// checking that there is a piece of the current player in the src cell
	if (!srcPiece || srcPiece->isBlack() != this->getCurrPlayer())
	{
		return NO_PIECE_IN_SRC;
	}

	// checking that there isnt a piece of the current player in the dst cell
	if (dstPiece && dstPiece->isBlack() == this->getCurrPlayer())
	{
		return PIECE_IN_DST;
	}

	// checking that the src and dest locations are valid
	if ((move[SRC_COL] > MAX_INDEX_COL || move[SRC_ROW] > MAX_INDEX_ROW || move[DEST_COL] > MAX_INDEX_COL || move[DEST_ROW] > MAX_INDEX_ROW) ||
		(move[SRC_COL] < MIN_INDEX_COL || move[SRC_ROW] < MIN_INDEX_ROW || move[DEST_COL] < MIN_INDEX_COL || move[DEST_ROW] < MIN_INDEX_ROW))
	{
		return INVALID_INDEX;
	}

	// the src cell is also the dest cell
	if (src == dst)
	{
		return SRC_IS_DST;
	}

	// check if the move is valid for the piece and it is not blocked by other piece
	if (!srcPiece->isMoveValidPiece(move) || this->isBlockingPiece(dst, src, srcPiece->pieceType()))
	{
		return INVALID_PIECE_MOVE;
	}

	this->removePiece(dst);
	srcPiece->setLocation(dst);
	this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
	this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

	if (currKing && this->isKingAttacked(currKing))
	{
		// undoing the move if a self check was activated
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		else
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

		return SELF_CHECK;
	}

	// checking if a check is made by making the move
	if (otherKing && this->isKingAttacked(otherKing))
	{
		// undoing the move if a check was made on the other king
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		else
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

		return VALID_MOVE_CHECK;
	}

	if (dstPiece)
	{
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
		dstPiece->setIsAlive(true);
	}
	else
	{
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
	}
	srcPiece->setLocation(src);
	this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

	return VALID_MOVE;
}

// printing the board
void Board::printBoard()
{
	std::cout << std::endl;
	std::cout << "  a b c d e f g h" << std::endl;
	for (int i = BOARD_SIZE; i > 0; i--)
	{
		std::cout << i << " ";

		for (int j = BOARD_SIZE; j > 0; j--)
		{
			std::cout << this->_board[i - 1][j] << " ";
		}
	}

}

// making the move (only if its a valid one)
CODES Board::makeMove(std::string move)
{
	// getting the pieces at the dest and src locations
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);
	CODES resultCode = this->isMoveValid(move);
	King* otherKing = nullptr;

	// printing the result
	std::cout << "\n" << "RESULT CODE: " << (char)resultCode << "\n";

	// making the move if its valid
	if (resultCode == VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// removing the piece at the dst (if there is one) and moving the src piece to the dst location
		this->removePiece(dst);
		srcPiece->setLocation(dst);
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
		this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

		if (resultCode == VALID_MOVE_CHECK)
		{
			otherKing = this->getKing(!this->getCurrPlayer());
			resultCode = checkmate::isCheckmate(*this, otherKing, this->isKingAttacked(otherKing));
			setCurrPlayer(!this->_currPlayer); // changing player
		}
		setCurrPlayer(!this->_currPlayer); // changing player
	}

	return resultCode;
}

// finding the king in the inputted color.
King* Board::getKing(bool isBlack)
{
	// getting the type of the king
	char typeOfKing = isBlack ? BLACK_KING : WHITE_KING;

	// returning the king according to the inputted player
	for (unsigned int i = 0; i < this->_pieces.size(); i++)
	{
		if (this->_pieces[i]->pieceType() == typeOfKing)
		{
			return (King*)(this->_pieces[i]);
		}
	}
	return nullptr;
}

// checking if there is a piece that blocks the move
bool Board::isBlockingPiece(std::string dst, std::string src, char type)
{
	int index = SRC_COL; // change the color
	int change = 0; // check the location
	int sideChange = 0; // diagonal moves
	bool isDiagonal = handle::moveDiagonally(src + dst);

	// checking for a blocking piece when the src piece is a rook
	if (type == WHITE_ROOK || type == BLACK_ROOK || ((type == WHITE_QUEEN || type == BLACK_QUEEN) && !isDiagonal))
	{
		if (dst[SRC_COL] == src[SRC_COL]) // check what is changing (color or row)
		{
			index = SRC_ROW; // changing the row
		}
		change = dst[index] > src[index] ? 1 : -1;
		while (dst != src)
		{
			src[index] += change;
			if (this->getPiece(src) && src != dst)
			{
				return true;
			}
		}
	}



// getting the type of piece in cell [x][y] in the board
char Board::getPieceAt(char x, char y)
{
	if (x >= MIN_INDEX_ROW && x <= MAX_INDEX_ROW && y >= MIN_INDEX_COL && y <= MAX_INDEX_COL)
	{
		return this->_board[(int)(BOARD_SIZE - (x - MIN_INDEX_ROW)) - 1][(int)(y - MIN_INDEX_COL)];
	}
	else
	{
		return 0;
	}
}

// creating the initial string to be sent to the frontend
char* Board::initialBoardString()
{
	char* initBoard = new char[BOARD_SIZE * BOARD_SIZE + 2];

	// copying the starting board of the game into the first 64 chars of the string
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		initBoard[i] = STARTING_BOARD[i];
	}

	initBoard[BOARD_SIZE * BOARD_SIZE] = (char)('0' + this->getCurrPlayer()); // putting the starting player into the last char
	initBoard[BOARD_SIZE * BOARD_SIZE + 1] = '\0';
	return initBoard;
}