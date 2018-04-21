#ifndef _VARS_H
#define _VARS_H
#pragma once
enum Color{White,Black};
struct Coord{
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
