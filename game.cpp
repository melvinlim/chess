#include<iostream>
#include"game.h"
using namespace std;
Game::Game(){
	board=new Board();
	board->reset();
	p1=new Human(White,board);
	p2=new Human(Black,board);
	move.quit=false;
	running=true;
}
void Game::start(){
	while(running){
		step();
	}
}
void Game::step(){
//	board->debug();
//	board->display(false);
	board->display();
	p1->decide(move);
	if(move.quit){
		running=false;
		return;
	}
	board->move(move);
}
