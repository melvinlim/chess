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
	printf("\nlegalmoves:");
	player->legalMoves->print();
	printf("\nkingSquare:");
	player->kingSquare->print();
	printf("\ncheck:");
	Rules::checked(player->nextPlayer) ? printf("true") : printf("false");
	printf("\n");
//	board->whitePieces->print();
//	board->blackPieces->print();
	Move tmpMove;
	Piece *p;
	for(;;){
		valid=false;
		while(!valid){
			player->decide(move);
			if(move.quit){
				running=false;
				return;
			}
			valid=Rules::verify(player->color,board,move);
		}
		p=board->move(move);
		if(!Rules::checked(player)){
			break;
		}
		printf("move cannot result in king being under attack.\n");
		tmpMove.src.i=move.dst.i;
		tmpMove.src.j=move.dst.j;
		tmpMove.dst.i=move.src.i;
		tmpMove.dst.j=move.src.j;
		board->move(tmpMove);
		if(p){
			board->square[move.dst.i][move.dst.j]->piece=p;
			p->square=board->square[move.dst.i][move.dst.j];
			p->place();
		}
	}
	
	if(p){
		player->captured->add(p);
		player->nextPlayer->pieces->remove(p);
	}
}
