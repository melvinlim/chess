#ifndef _SQUARE_H
#define _SQUARE_H
#include<string>
//#include"board.h"
//class Board;
using namespace std;
class Piece;
class Square{
public:
	int i,j;
//	Board *board;
	Piece *piece;
	string strId;
	bool valid;
	Square();
	void clearAndLabel(int,int);
	void place(Piece *p);
	void display();
	void print();
	void printAll();
};
#endif
