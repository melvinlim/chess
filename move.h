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
	void print() const{
		char buf1[256];
		char buf2[256];
		Utility::coordToString(buf1,src);
		Utility::coordToString(buf2,dst);
//		printf("(%d,%d)->(%d,%d) ",src.i,src.j,dst.i,dst.j);
		printf(" %s->%s",buf1,buf2);
	}
	Move();
	Move(const int &,const int &,const int &,const int &);
	Move(const struct Coord &,const struct Coord &);
	Move(const Move &);
	~Move();
	Move(Piece *);
	Move(Move *);
};
#endif
