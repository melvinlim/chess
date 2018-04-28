#ifndef _MOVE_H
#define _MOVE_H
#include"defs.h"
#include"utility.h"
#include"square.h"
#include"piece.h"
#include<string>
class Square;
class Piece;
class Move{
public:
	Square *dstSquare;
	Piece *piece;
	struct Coord src;
	struct Coord dst;
	bool valid;
	bool isCapture;
	bool quit;
	void print(){
		Utility::coordToString(src.str,src);
		Utility::coordToString(dst.str,dst);
//		printf("(%d,%d)->(%d,%d) ",src.i,src.j,dst.i,dst.j);
		printf(" %s->%s",src.str,dst.str);
	}
	Move();
	Move(Move *);
};
#endif
