#include<stdio.h>
#include"board.h"
int main(){
	Board *board=new Board();
	board->reset();
	board->display();
}
