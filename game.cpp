#include"game.h"
using namespace std;
Game::Game(){
	board=new Board();
	board->players=this->players;
	p1=new Human(White,board);
	p2=new Random(Black,board);
	p1->nextPlayer=p2;
	p2->nextPlayer=p1;
	players[0]=p1;
	players[1]=p2;
	activePlayer=p1;
	move.quit=false;
	board->placeAllPieces();
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
	printf("pieces:");
	player->pieces->print();
	printf("\ncaptured:");
	player->captured->print();
	printf("\nthreats:");
	player->threats->print();
	printf("\nkingSquare:");
	player->kingSquare->print();
	printf("\n");
//	board->whitePieces->print();
//	board->blackPieces->print();
	valid=false;
	while(!valid){
		player->decide(move);
		if(move.quit){
			running=false;
			return;
		}
		valid=Rules::verify(player->color,board,move);
	}
	Piece *p=board->move(move);
	if(p){
		player->captured->add(p);
		player->nextPlayer->pieces->remove(p);
	}
}
