#include "Pawn.h"

#define WHITE_PAWNS_STARTING_ROW 1
#define BLACK_PAWNS_STARTING_ROW 6


Pawn::Pawn(Coord coord, Color color) : Piece(coord, color)
{
    if (this->_color == WHITE_PIECE) // if its a white piece (white == got rights)
    {
        this->_sign = WhitePawn; // setting the sign to a white pawn
    }
    else // its a black piece (black == no rights)
    {
        this->_sign = BlackPawn; // setting the sign to a black pawn
    }
}

MoveResult Pawn::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
{
    auto dstInPathResult = isDstInPath(dst); // store the returned tuple
    // extract the values
    bool isInPath;
    Direction direction;
    std::tie(isInPath, direction) = dstInPathResult;

    if (!isInPath) // if the destination is not in path
    {
        return IllegalPieceMove;
    }


    auto tupleRes = isEatingMove(board, direction, dst); // store the returned tuple
    // extract the values
    bool isEating;
    MoveResult legality;
    std::tie(isEating, legality) = tupleRes;

    if (isEating) // check if the move is an eating move
    {
        return legality; // return the legality of the move
    }

    // check if there are pieces in the way that disallows the piece to move there
    if (arePiecesInWay(board, direction, dst))
    {
        return IllegalPieceMove;
    }
    return Legal;
}

bool Pawn::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
    Coord currentCoord = calcDst(this->_coord, 1, direction);
    Coord extraDest = calcDst(dst, 1, direction);

    while (!currentCoord.isEqual(extraDest)) // while we havent reached the destination yet
    {
        if (board[currentCoord.Row][currentCoord.Col] != NULL)
        {
            return true; // piece are in the way
        }
        currentCoord = calcDst(currentCoord, 1, direction); // go to the next coord
    }

    return false; // there are no pieces in the way
}

std::tuple<bool, Direction> Pawn::isDstInPath(Coord dst)
{



    if (this->_color == WHITE_PIECE && this->_coord.Row > dst.Row) // we are white and the destination piece is below us
    {
        return std::make_tuple(false, None); // return false and garbage direction
    }
    else if (this->_color == BLACK_PIECE && this->_coord.Row < dst.Row) // we are black and the destination piece is above us
    {
        return std::make_tuple(false, None); // return false and garbage direction
    }


    auto tupleRes = calcUnsignedDelta(this->_coord, dst); // store the returned tuple
    // extract the values
    int deltaRow;
    int deltaCol;
    std::tie(deltaRow, deltaCol) = tupleRes;



    if ((deltaRow == 2 && isInStartingPosition() && deltaCol == 0) // if its moving two spaces from its starting position
        ||
        (deltaRow == 1 && deltaCol <= 1)) // if its moving one space forwards
    {
        return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction
    }

    return std::make_tuple(false, None); // return false and garbage direction
}

bool Pawn::isInStartingPosition()
{
    if (this->_color == WHITE_PIECE)
    {
        return this->_coord.Row == WHITE_PAWNS_STARTING_ROW; // return if the piece is in its starting row
    }
    // the piece is black
    return this->_coord.Row == BLACK_PAWNS_STARTING_ROW; // return if the piece is in its starting row
}

std::tuple<bool, MoveResult> Pawn::isEatingMove(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
    if (direction == UP || direction == DOWN)
    {
        return std::make_tuple(false, NoResult); // its not an eating move
    }

    if (board[dst.Row][dst.Col] == NULL) // target piece is null
    {
        return std::make_tuple(true, IllegalPieceMove); // its an eating move just not a valid one
    }
    return  std::make_tuple(true, Legal);
}