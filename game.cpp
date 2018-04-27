#include"game.h"
using namespace std;
int nLegalMoves(Player *player){
	int count=0;
	Node<Move *> *sptr;
	sptr=player->globalMoves->list.root;
	while(sptr->next){
		sptr=sptr->next;
		if(sptr->item->valid)	count++;
	}
	return count;
}
void printInvalidated(Move *move){
	if(!move->valid){
		move->print();
		//printf("%s ",square->strId.data());
	}
}
Game::Game(){
	board=new Board();
	board->players=this->players;
	p1=new Human(White,board);
//	p2=new Human(Black,board);
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
void Game::testMove(const char *src,const char *dst){
	Move move;
	Piece *p;
//	gameOver(activePlayer);
	Utility::stringToCoord(src,move.src);
	Utility::stringToCoord(dst,move.dst);
	p=board->move(move);
	if(p){
		activePlayer->captured->add(p);
		activePlayer->nextPlayer->pieces->remove(p);
	}
	activePlayer=activePlayer->nextPlayer;
}
void Game::test(){
	testMove("e2","e4");
	testMove("e7","e5");
	testMove("f1","c4");
	testMove("a7","a6");
	testMove("d1","f3");
	testMove("a6","a5");
}
void Game::start(){
	test();
	while(running){
		step();
	}
}
void Game::step(){
	step(activePlayer);
	if(!running)	return;
	activePlayer=activePlayer->nextPlayer;
}
void validate(Move *move){
	move->valid=true;
}
bool Game::gameOver(Player *player){
	Piece *p;
	bool invalidMove;
	Move testMove,tmpMove;
	Node<Move *> *sptr=player->globalMoves->list.root;
	bool escapePossible=false;
	delete player->originalMoves;
	player->originalMoves=new Collection<Move *>(player->globalMoves);
	player->globalMoves->list.apply(validate);
		invalidMove=false;
		while(sptr->next){
			sptr=sptr->next;
			testMove.src.i=sptr->item->src.i;
			testMove.src.j=sptr->item->src.j;
			testMove.dst.i=sptr->item->dst.i;
			testMove.dst.j=sptr->item->dst.j;
			if((testMove.dst.i==testMove.src.i)&&(testMove.dst.j==testMove.src.j)){
				assert(false);
			}
			p=board->move(testMove);
			if(Rules::checked(player)){
				printf("checked\n");
				invalidMove=true;
			}else{
				escapePossible=true;
			}
			tmpMove.src.i=testMove.dst.i;
			tmpMove.src.j=testMove.dst.j;
			tmpMove.dst.i=testMove.src.i;
			tmpMove.dst.j=testMove.src.j;
			if(board->square[tmpMove.src.i][tmpMove.src.j]->piece==0){
				assert(false);
			}
			board->move(tmpMove);
			if(p){
				board->square[testMove.dst.i][testMove.dst.j]->piece=p;
				p->square=board->square[testMove.dst.i][testMove.dst.j];
				p->place();
			}
			if(invalidMove){
				sptr->item->valid=false;
				board->square[testMove.dst.i][testMove.dst.j]->valid=false;
				printf("((%d))\n",nLegalMoves(player));
				printf("removing:%s\t",board->square[testMove.dst.i][testMove.dst.j]->strId.data());
//				printf("sz0:%d,%d\t",sptr->item->size(),player->legalMoves->size());
				//pptr->item->legalMoves->remove(board->square[testMove.dst.i][testMove.dst.j]);
				//player->legalMoves->remove(board->square[testMove.dst.i][testMove.dst.j]);
//				printf("sz1:%d,%d\n",sptr->item->size(),player->legalMoves->size());
			}
		}
	//if(!player->legalMoves->isEmpty())	return false;
	if(escapePossible)	return false;
	if(Rules::checked(player)){
		player->result=Lose;
		player->nextPlayer->result=Win;
	}else{
		player->result=Draw;
		player->nextPlayer->result=Draw;
	}
	return true;
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
	printf("\nattacks:");
	player->globalAttacks->print();
	printf("\nlegalmoves:");
	player->globalMoves->print();
	printf("\ninvalidated:");
	player->globalMoves->list.apply(printInvalidated);
	printf("\n((%d))",nLegalMoves(player));
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
