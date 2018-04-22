#ifndef _BOARD_H
#define _BOARD_H
#pragma once
#include<stdio.h>
#include"square.h"
#include"collection.h"
#include"piece.h"
#include"defs.h"
class Board{
public:
	Collection<Piece *> *whitePieces;
	Collection<Piece *> *blackPieces;
	Square *square[8][8];
	Board();
	~Board();
	void placePiece(int,int,enum Color color,Piece *);
	void placeSidePieces(int row,enum Color color);
	void placeRowPieces(int row,enum Color color);
	void placeRowPawns(int row,enum Color color);
	void placePieces();
	void placePawns();
	void reset();
	void debug();
	void display(bool labels=true);
	Piece *move(Move &);
};
#endif
