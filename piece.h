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
	virtual void addThreats(Collection<Square *> *)=0;
};
class King:public Piece{
public:
	King(Color color);
	void addThreats(Collection<Square *> *);
};
class Pawn:public Piece{
public:
	Pawn(Color color);
	void addThreats(Collection<Square *> *);
};
class Queen:public Piece{
public:
	Queen(Color color);
	void addThreats(Collection<Square *> *);
};
class Knight:public Piece{
public:
	Knight(Color color);
	void addThreats(Collection<Square *> *);
};
class Bishop:public Piece{
public:
	Bishop(Color color);
	void addThreats(Collection<Square *> *);
};
class Rook:public Piece{
public:
	Rook(Color color);
	void addThreats(Collection<Square *> *);
};
#endif
