#pragma once
#include <iostream>
#include <math.h>

enum INDEX_MOVMENTS { SRC_COL = 0, SRC_ROW = 1, DEST_COL = 2, DEST_ROW = 3 };

#define KNIGHT_MOVING_PATTERN_NUM 2

class handle
{
public:
	handle();
	~handle();
	static int moveSideways(std::string move);
	static int moveBackOrForward(std::string move);
	static int moveDiagonally(std::string move);
	static bool singleMove(std::string move);
};