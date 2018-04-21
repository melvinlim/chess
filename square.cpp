#include"square.h"
Square::Square(int id){
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
void Square::place(Piece *p){
	this->piece=p;
//	piece->square=this;
}
void Square::display(){
	if(piece){
		piece->display();
	}else{
		printf("  ");
	}
}
