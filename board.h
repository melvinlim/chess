#ifndef _BOARD_H
#define _BOARD_H
#pragma once
#include<stdio.h>
#include"square.h"
#include"collection.h"
#include"piece.h"
#include"player.h"
#include"defs.h"
#include"move.h"
class Move;
class Player;
class Square;
class Piece;
class Board{
public:
	Player **players;
	Player *whitePlayer;
	Player *blackPlayer;
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
	void placeAllPieces();
	void removeAllPieces();
	void debug();
	void display(const bool=true);
	Piece *makeMove(const Move &,const bool=true);
};
#endif
