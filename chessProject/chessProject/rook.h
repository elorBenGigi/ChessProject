#pragma once
#ifndef ROOK_H
#define ROOK_H
#include <vector>
#include <string>

class Rook {
public:
    static bool isMoveValid(const std::vector<std::string>& board, int startX, int startY, int endX, int endY);
};

#endif