#include<iostream>
#include"game.h"
using namespace std;
Game::Game(){
	board=new Board();
	board->reset();
	p1=new Human(White,board);
	p2=new Human(Black,board);
	p1->nextPlayer=p2;
	p2->nextPlayer=p1;
	activePlayer=p1;
	move.quit=false;
	running=true;
}
void Game::start(){
	while(running){
		step();
	}
}
void Game::step(){
	step(activePlayer);
	activePlayer=activePlayer->nextPlayer;
}
void Game::step(Player *player){
//	board->debug();
//	board->display(false);
	board->display();
	valid=false;
	while(!valid){
		player->decide(move);
		if(move.quit){
			running=false;
			return;
		}
		valid=rules.verify(player->color,board,move);
	}
	board->move(move);
}
