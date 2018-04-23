#ifndef _PIECE_H
#define _PIECE_H
#pragma once
#include<string>
#include"defs.h"
#include"collection.h"
#include"rules.h"
#include"square.h"
#include"player.h"
using namespace std;
class Square;
class Player;
class Piece{
public:
	enum Color color;
	Collection<Square *> *threats;
	int forwardDirection;
	Player *player;
	PieceType type;
	Square *square;
	string self;
	Piece(Color color);
	void display();
	void print();
	void setSelf(string s);
	virtual void place();
	virtual void addThreats(Collection<Square *> *)=0;
};
class King:public Piece{
public:
	King(Color color);
	void addThreats(Collection<Square *> *);
	void place();
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
