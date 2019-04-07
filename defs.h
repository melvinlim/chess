#ifndef _VARS_H
#define _VARS_H
#include<stdio.h>
#define MAXMOVESZ (14+14+14+14+8+8+28+8)
//#define DEBUG
enum Result{
	Playing,
	Win,
	Lose,
	Draw
};
enum Color{
	White,
	Black
};
enum PieceType{
	PawnT,
	KnightT,
	BishopT,
	RookT,
	QueenT,
	KingT
};
struct Coord{
	int i;
	int j;
};
#endif
