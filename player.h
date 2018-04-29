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
	Piece *promotedPawn;
	Square *kingSquare;
	Player *nextPlayer;
	bool isChecked();
	string str;
	char colorStr[5];
	enum Color color;
	enum Result result;
	Board *board;
//	Move *previousMove;
	void reset();
	void updateGlobalMoves();
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
