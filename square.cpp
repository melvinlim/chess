#include"square.h"
Square::Square(int i,int j,Board *board){
	piece=0;
	this->i=i;
	this->j=j;
	this->board=board;
	strId="  ";
	int column=j;
	int row=i;
	int reversedRow=8-row;
	strId[0]=(column)+65;
	strId[1]=(reversedRow)+48;
	attackers=new Collection<Piece *>();
	//printf("%s\n",strId.data());
	//printf("%d %d\n",i,j);
}
void Square::place(Piece *p){
	this->piece=p;
	piece->square=this;
}
void Square::display(){
	if(piece){
		piece->display();
	}else{
		printf("  ");
	}
}
void Square::print(){
	printf("[");
	if(attackers){
		attackers->print();
	}
	printf("]");
	printf(":%s ",strId.data());
}
