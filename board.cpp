#include<stdio.h>
#include<string>
#include"piece.h"
using namespace std;
class Square{
public:
	Piece *piece;
	string strId;
	Square(int id){
		piece=0;
		this->id=id;
		strId="  ";
		int column=id%8;
		int row=id/8;
		int reversedRow=8-row;
		strId[0]=(column)+65;
		strId[1]=(reversedRow)+48;
		
		//printf("%s\n",strId.data());
		//printf("%d\n",this->id);
	}
	void place(Piece *p){
		piece=p;
	}
	void display(){
		if(piece){
			piece->display();
		}else{
			printf("  ");
		}
	}
private:
	int id;
};
class Board{
public:
	Square *square[8][8];
	Board(){
		int id=0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				square[i][j]=new Square(id++);
			}
		}
	}
	void placeRow(int row,enum Color color){
		int loc;
		Piece *p;
		for(int j=0;j<8;j++){
			loc=(row*8)+j;
			p=new Pawn(color,loc);
			square[row][j]->place(p);
		}
	}
	void placePawns(){
		placeRow(1,Black);
		placeRow(6,White);
	}
	void reset(){
		Piece *p;
		int loc;
		loc=(0*8)+4;
		p=new King(White,loc);
		square[7][4]->place(p);
		loc=(7*8)+4;
		p=new King(Black,loc);
		square[0][4]->place(p);
		placePawns();
	}
	void debug(){
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
	void display(bool labels=true){
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
};
