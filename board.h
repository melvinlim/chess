#ifndef _BOARD_H
#define _BOARD_H
#pragma once
#include"square.h"
#include"defs.h"
//class Square;
class Board{
public:
	Square *square[8][8];
	Board();
	~Board();
	void placeRow(int row,enum Color color);
	void placePawns();
	void reset();
	void debug();
	void display(bool labels=true);
};
#endif
