#ifndef _SQUARE_H
#define _SQUARE_H
#include<string>
#include"piece.h"
#include"board.h"
class Board;
using namespace std;
class Piece;
class Square{
public:
	int i,j;
	Board *board;
	Collection<Piece *> *threats;
	Piece *piece;
	string strId;
	Square(int,int,Board *);
	void place(Piece *p);
	void display();
	void print();
};
#endif
