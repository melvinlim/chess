#include"game.h"
using namespace std;
Game::Game(){
	board=new Board();
	board->players=this->players;
	p1=new Human(White,board);
	p2=new Human(Black,board);
//	p2=new Random(Black,board);
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
	if(!running)	return;
	activePlayer=activePlayer->nextPlayer;
}
bool Game::gameOver(Player *player){
	if(player->legalMoves->isEmpty()){
		if(!Rules::checked(player)){
			player->result=Draw;
			player->nextPlayer->result=Draw;
			return true;
		}
	}
	if(Rules::checked(player)){
		Piece *p;
		Move testMove,tmpMove;
		Node<Square *> *sptr;
		Node<Piece *> *pptr=player->pieces->list.root;
		while(pptr->next){
			pptr=pptr->next;
			sptr=pptr->item->legalMoves->list.root;
			testMove.src.i=pptr->item->square->i;
			testMove.src.j=pptr->item->square->j;
			while(sptr->next){
				sptr=sptr->next;
				testMove.dst.i=sptr->item->i;
				testMove.dst.j=sptr->item->j;
				p=board->move(testMove);
				if(!Rules::checked(player)){
					return false;
				}
				tmpMove.src.i=testMove.dst.i;
				tmpMove.src.j=testMove.dst.j;
				tmpMove.dst.i=testMove.src.i;
				tmpMove.dst.j=testMove.src.j;
				board->move(tmpMove);
				if(p){
					board->square[testMove.dst.i][testMove.dst.j]->piece=p;
					p->square=board->square[testMove.dst.i][testMove.dst.j];
					p->place();
				}
			}
		}
		return true;
	}
	return false;
}
void Game::step(Player *player){
	if(gameOver(player)){
		printf("game over\n");
		running=false;
		return;
	}
//	board->debug();
//	board->display(false);
	board->display();
	printf("pieces:");
	player->pieces->print();
	printf("\ncaptured:");
	player->captured->print();
	printf("\nthreats:");
	player->threats->printAll();
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
