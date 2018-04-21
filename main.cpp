//#include<stdio.h>
#include"board.h"
int main(){
	Board *board=new Board();
	board->reset();
	board->debug();
	board->display(false);
//	board->display();
	return 0;
}
