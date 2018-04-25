#ifndef _VARS_H
#define _VARS_H
#pragma once
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
	char str[2];
	int i;
	int j;
};
struct Move{
	struct Coord src;
	struct Coord dst;
	bool valid;
	bool quit;
};
#endif
