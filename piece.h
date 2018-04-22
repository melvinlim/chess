#ifndef _PIECE_H
#define _PIECE_H
#pragma once
#include<string>
#include"defs.h"
#include"collection.h"
#include"square.h"
using namespace std;
class Square;
class Piece{
public:
	enum Color color;
	PieceType type;
	Square *square;
	string self;
	Piece(Color color);
	void display();
	void setSelf(string s);
	void addThreats(Collection<Square *> *);
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
class Knight:public Piece{
public:
	Knight(Color color);
};
class Bishop:public Piece{
public:
	Bishop(Color color);
};
class Rook:public Piece{
public:
	Rook(Color color);
};
#endif
