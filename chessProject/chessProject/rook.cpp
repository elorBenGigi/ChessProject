#include "Rook.h"

bool Rook::isMoveValid(const std::vector<std::string>& board, int startX, int startY, int endX, int endY) {
    if (startX != endX && startY != endY) return false; // Rook moves in straight lines

    int xDir = (endX - startX) ? ((endX - startX) > 0 ? 1 : -1) : 0;
    int yDir = (endY - startY) ? ((endY - startY) > 0 ? 1 : -1) : 0;

    int x = startX + xDir;
    int y = startY + yDir;

    while (x != endX || y != endY) {
        if (board[x][y] != '#') return false; // Path must be clear
        x += xDir;
        y += yDir;
    }

    return true;
}