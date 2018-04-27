#ifndef _UTILITY_H
#define _UTILITY_H
#include"defs.h"
#include<string>
namespace Utility{
	void stringToCoord(const std::string s,Coord &coord);
	void coordToString(char *str,const Coord &coord);
};
class Move{
public:
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
	Move(){	valid=true;}
};
#endif
