#ifndef _VARS_H
#define _VARS_H
#include<stdio.h>
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
	char str[3];
	int i;
	int j;
};
#endif
