#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"board.h"
#include"utility.h"
#include"rules.h"
#include"collection.h"
#include"piece.h"
#include"move.h"
#include<string>
#include<iostream>
using namespace std;
class Square;
class Move;
class Piece;
class Board;
class Player{
public:
	Collection<Move *> *globalMoves;
	Collection<Piece *> *pieces;
	Collection<Piece *> *captured;
	Collection<Move *> *originalMoves;
	Square *kingSquare;
	Player *nextPlayer;
	string str;
	char colorStr[5];
	enum Color color;
	enum Result result;
	Board *board;
	//Move move;
	void reset();
	Player(enum Color,Board *);
	virtual void decide(Move &)=0;
	void initThreatsList();
};
class Random:public Player{
public:
	Random(enum Color,Board *);
	void decide(Move &);
};
class Human:public Player{
	int getCoord(string,Move &);
public:
	Human(enum Color,Board *);
	void decide(Move &);
};
#endif
