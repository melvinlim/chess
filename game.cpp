#include"game.h"
using namespace std;
int nLegalMoves(Player *player){
	int count=0;
	Node<Move *> *sptr;
	sptr=player->originalMoves->list.root;
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
//	p1=new Random(White,board);
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
void Game::reset(){
	p1->reset();
	p2->reset();
	board->removeAllPieces();
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
	p=board->makeMove(move);
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
//	test();
	for(;;){
		while(running){
			step();
		}
		reset();
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
	Node<Move *> *sptr;
	bool escapePossible=false;
	delete player->originalMoves;
	player->originalMoves=new Collection<Move *>(player->globalMoves);
	player->originalMoves->list.apply(validate);
	sptr=player->originalMoves->list.root;
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
		p=board->makeMove(testMove);
		if(player->isChecked()){
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
		board->makeMove(tmpMove);
		if(p){
			p->place(board->square[testMove.dst.i][testMove.dst.j]);
		}
		if(invalidMove){
			invalidMove=false;
			sptr->item->valid=false;
		}
	}
	//if(!player->legalMoves->isEmpty())	return false;
	if(escapePossible)	return false;
	if(player->isChecked()){
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
	printf("\nlegalmoves:");
	player->originalMoves->print();
	printf("\ninvalidated:");
	player->originalMoves->list.apply(printInvalidated);
	printf("\n((%d))",nLegalMoves(player));
	printf("\nkingSquare:");
	player->kingSquare->print();
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
			assert(valid);
		}
		player->promotedPawn=0;
		p=board->makeMove(move,false);
		if(!player->isChecked()){
			break;
		}
		assert(false);
		printf("move cannot result in king being under attack.\n");
		tmpMove.src.i=move.dst.i;
		tmpMove.src.j=move.dst.j;
		tmpMove.dst.i=move.src.i;
		tmpMove.dst.j=move.src.j;
		board->makeMove(tmpMove);
		if(p){
			board->square[move.dst.i][move.dst.j]->piece=p;
			p->place(board->square[move.dst.i][move.dst.j]);
		}
	}
	if(p){
		player->captured->add(p);
		player->nextPlayer->pieces->remove(p);
	}
	if(player->promotedPawn){
		Square *square=player->promotedPawn->square;
		Piece *p=new Queen(player->color);
		board->placePiece(square->i,square->j,player->color,p);
		player->pieces->remove(player->promotedPawn);
		player->promotedPawn->removePiece();
		delete player->promotedPawn;
		player->promotedPawn=0;
	}
}
