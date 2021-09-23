#ifndef _UTILITY_H
#define _UTILITY_H
#include"defs.h"
#include<string>
namespace Utility{
	void stringToCoord(const std::string s,Coord &coord);
	void coordToString(char *str,const Coord &coord);
};
#include"defs.h"
#include"utility.h"
#include"square.h"
#include"piece.h"
#include<string>
class Square;
class Piece;
class Move{
public:
//	Square *dstSquare;
	Piece *piece;
	struct Coord src;
	struct Coord dst;
	bool valid;
	bool isCapture;
	bool quit;
	void print();
	Move();
	Move(const int &,const int &,const int &,const int &);
	Move(const struct Coord &,const struct Coord &);
	Move(const Move &);
	~Move();
	Move(Piece *);
	Move(Move *);
};
#endif
