#ifndef _UTILITY_H
#define _UTILITY_H
#include"defs.h"
#include<string>
namespace Utility{
	void stringToCoord(const std::string s,Coord &coord);
	void coordToString(char *str,const Coord &coord);
};
#endif
