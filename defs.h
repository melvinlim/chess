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
	char str[2];
	int i;
	int j;
};
struct Move{
//public:
	struct Coord src;
	struct Coord dst;
	bool valid;
	bool isCapture;
	bool quit;
	void print(){
//		Utility::stringToCoord(src.str,src);
//		Utility::stringToCoord(dst.str,dst);
		printf("(%d,%d)->(%d,%d) ",src.i,src.j,dst.i,dst.j);
//		printf("(%s)->(%s) ",src.str,dst.str);
	}
};
#endif
