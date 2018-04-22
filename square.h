#ifndef _SQUARE_H
#define _SQUARE_H
#pragma once
#include<string>
#include"piece.h"
using namespace std;
class Piece;
class Square{
public:
	int i,j;
	Piece *piece;
	string strId;
	Square(int,int);
	void place(Piece *p);
	void display();
};
#endif
