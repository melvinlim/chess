#ifndef _SQUARE_H
#define _SQUARE_H
#pragma once
#include<string>
#include"piece.h"
using namespace std;
class Square{
public:
	Piece *piece;
	string strId;
	Square(int id);
	void place(Piece *p);
	void display();
	int id;
};
#endif
