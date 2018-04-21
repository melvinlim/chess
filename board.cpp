#include<stdio.h>
#include"board.h"
Board::Board(){
	int id=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			square[i][j]=new Square(id++);
		}
	}
}
Board::~Board(){}
void Board::placeRow(int row,enum Color color){
	Piece *p;
	for(int j=0;j<8;j++){
		p=new Pawn(color);
		square[row][j]->place(p);
		//assert(square[row][j]->id==p->square->id);
	}
}
void Board::placePawns(){
	placeRow(1,Black);
	placeRow(6,White);
}
void Board::reset(){
	Piece *p;
	p=new King(White);
	square[7][4]->place(p);
	p=new King(Black);
	square[0][4]->place(p);
	placePawns();
}
void Board::debug(){
	printf("+--+--+--+--+--+--+--+--+\n");
	for(int i=0;i<8;i++){
		printf("|");
		for(int j=0;j<8;j++){
			printf("%s",square[i][j]->strId.data());
			printf("|");
		}
		printf("\n+--+--+--+--+--+--+--+--+\n");
	}
}
void Board::display(bool labels){
	if(labels)	printf("  ");
	printf("+--+--+--+--+--+--+--+--+\n");
	for(int i=0;i<8;i++){
		if(labels)	printf("%c ",(7-i)+48+1);
		printf("|");
		for(int j=0;j<8;j++){
			square[i][j]->display();
			printf("|");
		}
		printf("\n");
		if(labels)	printf("  ");
		printf("+--+--+--+--+--+--+--+--+\n");
	}
	if(labels)	printf("    A  B  C  D  E  F  G  H\n");
}
