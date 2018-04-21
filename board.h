#ifndef _BOARD_H
#define _BOARD_H
#pragma once
#include"square.h"
#include"defs.h"
class Board{
public:
	Square *square[8][8];
	Board();
	~Board();
	void placeSidePieces(int row,enum Color color);
	void placeRowPieces(int row,enum Color color);
	void placeRowPawns(int row,enum Color color);
	void placePieces();
	void placePawns();
	void reset();
	void debug();
	void display(bool labels=true);
};
#endif
