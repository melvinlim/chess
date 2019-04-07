#ifndef _PIECE_H
#define _PIECE_H
#pragma once
#include<string>
#include"defs.h"
#include"collection.h"
#include"rules.h"
#include"player.h"
using namespace std;
class Square;
class Player;
class Piece{
public:
	enum Color color;
	int forwardDirection;
	Player *player;
	PieceType type;
	Square *square;
	string self;
	Piece(Color color);
	void display();
	void print();
	void setSelf(string s);
	void removePiece();
	virtual void place(Square *);
	virtual void addMoves()=0;
	virtual ~Piece(){};
	bool removed;
	bool hasMoved;
	bool enPassant;
};
class King:public Piece{
public:
	King(Color color);
	void addMoves();
	void place(Square *);
};
class Pawn:public Piece{
public:
	Pawn(Color color);
	void addMoves();
	void place(Square *);
};
class Queen:public Piece{
public:
	Queen(Color color);
	void addMoves();
};
class Knight:public Piece{
public:
	Knight(Color color);
	void addMoves();
};
class Bishop:public Piece{
public:
	Bishop(Color color);
	void addMoves();
};
class Rook:public Piece{
public:
	Rook(Color color);
	void addMoves();
};
#endif
