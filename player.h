#ifndef _PLAYER_H
#define _PLAYER_H
#include"defs.h"
class Player{
public:
	enum Color color;
	Move move;
	Player(enum Color);
	virtual bool decide(Move &)=0;
};
class Human:public Player{
public:
	Human(enum Color);
	bool decide(Move &);
};
#endif
