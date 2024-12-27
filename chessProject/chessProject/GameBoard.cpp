#include "GameBoard.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"

#define MAX_KING_MOVES 8

void GameBoard::init(std::string boardInput)
{
    // extract the turn from the string
    this->_turn = (Color)std::stoi(boardInput.substr(TURN_INDEX));;

    int stringIndex = 0;
    for (int Row = BOARD_ROWS - 1; Row >= 0; Row--)
    {
        for (int Col = 0; Col < BOARD_ROWS; Col++)
        {
            // get the piece char from the starting layout
            char pieceChar = boardInput[stringIndex];
            // create a new piece based on the piece char
            this->board[Row][Col] = createPiece(pieceChar, Coord(Row, Col));
            stringIndex++;
        }
    }
}

char GameBoard::execMove(Coord src, Coord dst)
{
    // check for invalid moves
    if (!src.isValid() || !dst.isValid()) // illegal coords
    {
        return InvalidSquareIndexes;
    }
    if (!isExist(src) || !isPieceTurn(src)) // source piece does not exist or not their turn
    {
        return NoPieceOnSourceSquare;
    }
    if (src.isEqual(dst)) // source and destination are the same
    {
        return SourceAndTargetSquaresEqual;
    }
    if (isExist(dst) && isPieceTurn(dst)) // destination is our own piece
    {
        return OwnPieceOnTargetSquare;
    }

    // check the move legality
    MoveResult moveResult = board[src.Row][src.Col]->checkMove(dst, board);
    if (moveResult == IllegalPieceMove)
    {
        return moveResult;
    }

    // check if it's a check (or self check, aka skill issue)
    MoveResult checkRes = checkCheck(src, dst);
    if (checkRes == SelfCheck) // if we put ourselves in check (illegal)
    {
        return checkRes;
    }
    else if (checkRes == LegalCheck) // if its a normal check (legal)
    {
        move(src, dst); // execute the move
        if (isCheckMate())
        {
            return CheckMate;
        }
        switchTurn(); // switch turns
        return checkRes;
    }

    // move the piece and return a valid move
    move(src, dst);
    switchTurn();
    return Legal; // all checks passed, its a legit move
}

bool GameBoard::isCheckMate()
{
    // get the opponent king coordinates
    Coord wantedKingCoord = getKing(alternativeTurn(this->_turn));

    // get all possible moves for the opponent king
    Coord possibleKingMoves[MAX_KING_MOVES];

    for (int i = 0; i < MAX_KING_MOVES; i++)
    {
        // calculate the destination of the king for each move
        Coord currDst = Piece::calcDst(wantedKingCoord, 1, (Direction)i);
        possibleKingMoves[i] = currDst;
    }

    // check if any move can save the king
    for (int i = 0; i < MAX_KING_MOVES; i++)
    {
        Coord currentMoveCoord = possibleKingMoves[i];
        if (!currentMoveCoord.isValid()) // if the move is invalid
        {
            continue;
        }

        GameBoard simulatedBoard = getCopyOfBoard(); // create a copy of the board
        simulatedBoard.switchTurn(); // switch turns

        if (simulatedBoard.isExist(currentMoveCoord) && simulatedBoard.isPieceTurn(currentMoveCoord)) // if destination is our own piece
        {
            continue;
        }

        simulatedBoard.move(wantedKingCoord, currentMoveCoord); // simulate the move

        if (!simulatedBoard.isPlayerKingInDanger()) // if the king is safe in the new position
        {
            return false; // king can escape, not checkmate
        }
    }

    // all moves lead to checkmate
    return true;
}

Color GameBoard::getTurn()
{
    return this->_turn; // return the current turn
}

void GameBoard::setTurn(Color newColor)
{
    this->_turn = newColor; // set the turn to the new turn
}

Piece* GameBoard::createPiece(char sign, Coord coord)
{
    switch (sign)
    {
    case BlackRook:
        return new Rook(coord, BLACK_PIECE);
    case BlackKnight:
        return new Knight(coord, BLACK_PIECE);
    case BlackBishop:
        return new Bishop(coord, BLACK_PIECE);
    case BlackKing:
        return new King(coord, BLACK_PIECE);
    case BlackQueen:
        return new Queen(coord, BLACK_PIECE);
    case BlackPawn:
        return new Pawn(coord, BLACK_PIECE);
    case WhiteRook:
        return new Rook(coord, WHITE_PIECE);
    case WhiteKnight:
        return new Knight(coord, WHITE_PIECE);
    case WhiteBishop:
        return new Bishop(coord, WHITE_PIECE);
    case WhiteKing:
        return new King(coord, WHITE_PIECE);
    case WhiteQueen:
        return new Queen(coord, WHITE_PIECE);
    case WhitePawn:
        return new Pawn(coord, WHITE_PIECE);
    case EmptySquare:
        return NULL;
    default:
        throw std::exception("Received an unexpected input (is this chess or Scrabble?)");
    }
}

bool GameBoard::isExist(Coord coord)
{
    // check if the piece exists in the board
    return this->board[coord.Row][coord.Col] != NULL;
}

bool GameBoard::isPieceTurn(Coord coord)
{
    // check if the piece color matches the current turn
    if (isExist(coord))
    {
        return board[coord.Row][coord.Col]->getColor() == this->_turn;
    }
    throw std::exception("Received null (that shouldn't happen!)");
}

Color GameBoard::alternativeTurn(Color currentTurn)
{
    return currentTurn == WHITE_PIECE ? BLACK_PIECE : WHITE_PIECE; // switch turns
}

void GameBoard::switchTurn()
{
    // switch the turn
    this->_turn = alternativeTurn(this->_turn);
}

GameBoard GameBoard::getCopyOfBoard()
{
    GameBoard newBoard; // create a new game board

    for (int row = 0; row < BOARD_ROWS; row++)
    {
        for (int col = 0; col < BOARD_COLS; col++)
        {
            Piece* currentPiece = this->board[row][col];
            if (currentPiece != NULL)
            {
                // copy the piece to the new board
                newBoard.board[row][col] = createPiece(currentPiece->getSign(), currentPiece->getCoord());
            }
            else
            {
                newBoard.board[row][col] = NULL;
            }
        }
    }
    newBoard.setTurn(this->_turn); // set the turn for the new board

    return newBoard; // return the new game board
}

MoveResult GameBoard::checkCheck(Coord src, Coord dst)
{
    GameBoard simulatedBoard = getCopyOfBoard(); // create a copy of the board
    simulatedBoard.move(src, dst); // simulate the move

    // now that we simulated the move we'll check if it causes a self check
    if (simulatedBoard.isPlayerKingInDanger())
    {
        return SelfCheck; // illegal move that causes self check
    }
    if (simulatedBoard.isOpponentKingInDanger())
    {
        return LegalCheck; // opponent king is in check
    }

    return Legal; // normal legal move
}

Coord GameBoard::getKing(Color wantedColor)
{
    // iterate through the board to find the king
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        for (int col = 0; col < BOARD_COLS; col++)
        {
            Piece* currentPiece = board[row][col];
            if (currentPiece == NULL)
            {
                continue;
            }
            if (currentPiece->getSign() == WhiteKing || currentPiece->getSign() == BlackKing)
            {
                if (currentPiece->getColor() == wantedColor)
                {
                    return currentPiece->getCoord(); // found the king, return its coordinates
                }
                else
                {
                    continue; // not the king we are looking for
                }
            }
        }
    }
    throw std::exception("No king found (are we playing checkers?)");
}


bool GameBoard::isPlayerKingInDanger()
{
	Coord wantedKingCoord = getKing(this->_turn); // get the coord of the king

	// iterate through the board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			try
			{
				Piece* currentPiece = board[row][col]; // get the current piece
				if (currentPiece == NULL)
				{
					continue;
				}
				if (!isPieceTurn(currentPiece->getCoord())) // if the current piece is an enemy piece
				{
					if (currentPiece->checkMove(wantedKingCoord, board) == Legal) // check if the piece can eat the king
					{
						return true; // return true because the player king is in danger
					}
				}
			}
			catch (...) // isPieceTurn threw an empty piece exception, ignore
			{
				continue;
			}
		}
	}
	return false; // our king is safe, the player king is not in danger
}

bool GameBoard::isOpponentKingInDanger()
{
	Coord wantedKingCoord = getKing(alternativeTurn(this->_turn)); // get the coord of the king

	// iterate through the board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			try
			{
				Piece* currentPiece = board[row][col]; // get the current piece
				if (currentPiece == NULL)
				{
					continue;
				}
				if (isPieceTurn(currentPiece->getCoord())) // if the current piece is an enemy piece
				{
					if (currentPiece->checkMove(wantedKingCoord, board) == Legal) // check if the piece can eat the king
					{
						return true; // return true because the player king is in danger
					}
				}
			}
			catch (...) // isPieceTurn threw an empty piece exception, ignore
			{
				continue;
			}
		}
	}
	return false; // our king is safe, the player king is not in danger
}

void GameBoard::move(Coord src, Coord dst)
{
	Piece* originalPiece = this->board[src.Row][src.Col]; // save the original piece
	this->board[src.Row][src.Col] = NULL; // set the 'old' coord to null
	this->board[dst.Row][dst.Col] = originalPiece; // set the 'new' coord to the new piece
	originalPiece->setCoord(dst); // update the coord of the piece
}