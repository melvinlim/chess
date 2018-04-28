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
	Collection<Move *> *localMoves;
	Collection<Move *> *localAttacks;
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
	virtual void addThreats(Collection<Move *> *)=0;
	virtual ~Piece(){};
	//virtual ~Piece(){delete localMoves;delete localAttacks;};
	bool removed;
};
class King:public Piece{
public:
	King(Color color);
	void addThreats(Collection<Move *> *);
	void place(Square *);
};
class Pawn:public Piece{
public:
	Pawn(Color color);
	void addThreats(Collection<Move *> *);
};
class Queen:public Piece{
public:
	Queen(Color color);
	void addThreats(Collection<Move *> *);
};
class Knight:public Piece{
public:
	Knight(Color color);
	void addThreats(Collection<Move *> *);
};
class Bishop:public Piece{
public:
	Bishop(Color color);
	void addThreats(Collection<Move *> *);
};
class Rook:public Piece{
public:
	Rook(Color color);
	void addThreats(Collection<Move *> *);
};
#endif
