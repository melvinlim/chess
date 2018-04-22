#ifndef _COLLECTION_H
#define _COLLECTION_H
#include<forward_list>
#include<iostream>
#include"piece.h"
using namespace std;
class Collection{
public:
	forward_list<Piece *> list;
	void add(Piece *);
	void remove(Piece *);
	void print();
};
#endif
