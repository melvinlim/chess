#ifndef _PIECE_H
#define _PIECE_H
#pragma once
#include<string>
#include"defs.h"
//#include"square.h"
using namespace std;
//enum Color{White,Black};
class Piece{
public:
	enum Color color;
//	Square *square;
	string self;
	Piece(Color color);
	void display();
};
class King:public Piece{
public:
	King(Color color);
};
class Pawn:public Piece{
public:
	Pawn(Color color);
};
class Queen:public Piece{
public:
	Queen(Color color);
};
#endif
