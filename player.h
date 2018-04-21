#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
#include"board.h"
#include"utility.h"
class Player{
public:
	Utility utility;
	enum Color color;
	Board *board;
	Move move;
	Player(enum Color,Board *board);
	virtual bool decide(Move &)=0;
};
class Human:public Player{
public:
	Human(enum Color,Board *board);
	bool decide(Move &);
};
#endif
