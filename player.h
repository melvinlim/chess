#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"board.h"
#include"utility.h"
#include<string>
#include<iostream>
using namespace std;
class Player{
public:
	Player *nextPlayer;
	string str;
	char colorStr[5];
	Utility utility;
	enum Color color;
	Board *board;
	Move move;
	Player(enum Color,Board *board);
	virtual void decide(Move &)=0;
};
class Human:public Player{
	int getCoord(string,Move &);
public:
	Human(enum Color,Board *board);
	void decide(Move &);
};
#endif
