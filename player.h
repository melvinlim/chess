#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"board.h"
#include"utility.h"
#include"rules.h"
#include"collection.h"
#include"piece.h"
#include<string>
#include<iostream>
using namespace std;
class Square;
class Piece;
class Board;
class Player{
public:
	Collection<Square *> *threats;
	Collection<Piece *> *pieces;
	Collection<Piece *> *captured;
	Player *nextPlayer;
	string str;
	char colorStr[5];
	enum Color color;
	Board *board;
	Move move;
	Player(enum Color,Board *);
	virtual void decide(Move &)=0;
	void initThreatsList();
};
class Human:public Player{
	int getCoord(string,Move &);
public:
	Human(enum Color,Board *);
	void decide(Move &);
};
#endif
