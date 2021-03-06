#include"game.h"
using namespace std;
int nLegalMoves(Player *player){
	int count=0;
	int n=player->globalMoves->size;
	for(int i=0;i<n;i++){
		if(player->globalMoves->atIndex(i)->valid)	count++;
	}
	return count;
}
void printPieces(std::list<Piece *> *stack){
	for(auto it=stack->begin();it!=stack->end();it++){
		(*it)->print();
	}
}
void printLegalMoves(Stack<Move *> *stack){
	Move *move;
	int n=stack->size;
	for(int i=0;i<n;i++){
		move=stack->atIndex(i);
		if(move->valid){
			move->print();
		}
	}
}
void printInvalidated(Stack<Move *> *stack){
	Move *move;
	int n=stack->size;
	for(int i=0;i<n;i++){
		move=stack->atIndex(i);
		if(!move->valid){
			move->print();
			//printf("%s ",square->strId.data());
		}
	}
}
void Game::printMoveList(){
	int i=1;
	for(auto rit=moveRecord.crbegin();rit!=moveRecord.crend();rit++){
		printf("\n%d:",i++);
		(*rit)->print();
	}
	printf("\n");
}
Game::Game(){
	board=new Board();
	board->players=this->players;
#ifdef DEBUG
	p1=new Random(White,board);
#else
	p1=new Human(White,board);
#endif
//	p2=new Human(Black,board);
	p2=new Random(Black,board);
	p1->nextPlayer=p2;
	p2->nextPlayer=p1;
	players[0]=p1;
	players[1]=p2;
	activePlayer=p1;
	board->whitePlayer=p1;
	board->blackPlayer=p2;
	board->whitePlayer->pieces=board->whitePieces;
	board->blackPlayer->pieces=board->blackPieces;
	currentMove.quit=false;
	board->placeAllPieces();
	running=true;
	moveNumber=0;
}
void Game::reset(){
	p1->reset();
	p2->reset();
	board->removeAllPieces();
	activePlayer=p1;
	currentMove.quit=false;
	board->whitePlayer->pieces=board->whitePieces;
	board->blackPlayer->pieces=board->blackPieces;
	board->placeAllPieces();
	running=true;
	moveNumber=0;
	Move *mptr;
	for(auto it=moveRecord.begin();it!=moveRecord.end();it++){
		mptr=*it;
		delete mptr;
	}
	moveRecord.clear();
}
void Game::testMove(const char *src,const char *dst){
	Move move;
	Piece *p;
	gameOver(activePlayer);
	Utility::stringToCoord(src,move.src);
	Utility::stringToCoord(dst,move.dst);
	p=board->makeMove(move);
	addToRecord(move);
	if(p){
		activePlayer->captured->push_back(p);
		activePlayer->nextPlayer->pieces->remove(p);
	}
	activePlayer=activePlayer->nextPlayer;
}
void Game::test(){
	testMove("e2","e4");
	testMove("b8","a6");
	testMove("e4","e5");
//	testMove("d7","d5");
/*
	testMove("e7","e5");
	testMove("f1","c4");
	testMove("a7","a6");
	testMove("d1","f3");
	testMove("a6","a5");
*/
}
void Game::addToRecord(const Move &item){
	Move *newRecord=new Move(item);
	moveRecord.push_front(newRecord);
	activePlayer->previousMove=newRecord;
}
void Game::start(){
//	test();
	for(;;){
		while(running){
			step();
		}
#ifdef DEBUG
board->display(1);
char ch=getchar();
if(ch=='q')
	return;
#endif
		reset();
	}
}
void Game::step(){
	moveNumber++;
	step(activePlayer);
	if(!running)	return;
	activePlayer=activePlayer->nextPlayer;
#ifdef DEBUG
if(moveNumber>=500)	running=false;
#endif
}
void validate(Move *move){
	move->valid=true;
}
bool Game::gameOver(Player *player){
	Piece *p;
	bool invalidMove;
	Move moveForward,moveBack;
	//Node<Move *> *sptr;
	Move *mptr;
	bool escapePossible=false;
	int n=player->globalMoves->size;
	for(int i=0;i<n;i++){
		validate(player->globalMoves->atIndex(i));
	}
//	player->globalMoves->list.apply(validate);
//	sptr=player->globalMoves->list.root;
	invalidMove=false;
	for(int i=0;i<n;i++){
		mptr=player->globalMoves->atIndex(i);
		moveForward.src=mptr->src;
		moveForward.dst=mptr->dst;
		if((moveForward.dst.i==moveForward.src.i)&&(moveForward.dst.j==moveForward.src.j)){
			assert(false);
		}
		p=board->makeMove(moveForward);
		if(player->isChecked()){
			invalidMove=true;
		}else{
			escapePossible=true;
		}
		moveBack.src=moveForward.dst;
		moveBack.dst=moveForward.src;
		if(board->square[moveBack.src.i][moveBack.src.j].piece==0){
			assert(false);
		}
		board->makeMove(moveBack);
		if(p){
			p->place(&board->square[moveForward.dst.i][moveForward.dst.j]);
		}
		if(invalidMove){
			invalidMove=false;
			//sptr->item->valid=false;
			mptr->valid=false;
		}
	}
	//if(!player->legalMoves->isEmpty())	return false;
	if(escapePossible)	return false;
	moveRecord.front()->print();
	if(player->isChecked()){
		printf("\ncheckmate detected\n");
		player->result=Lose;
		player->nextPlayer->result=Win;
	}else{
		printf("\nstalemate detected\n");
		player->result=Draw;
		player->nextPlayer->result=Draw;
	}
	printf("\nlegalmoves:");
//	player->globalMoves->print();
	printLegalMoves(player->globalMoves);
	printf("\ninvalidated:");
	//player->globalMoves->list.apply(printInvalidated);
	printInvalidated(player->globalMoves);
	printf("\n((%d))",nLegalMoves(player));
	return true;
}
bool Game::isValidMove(const Move &move){
	Move *mptr;
	int n=activePlayer->globalMoves->size;
	for(int i=0;i<n;i++){
		mptr=activePlayer->globalMoves->atIndex(i);
		if(mptr->valid){
			if(	(mptr->src.i==move.src.i)	&&
					(mptr->src.j==move.src.j)	&&
					(mptr->dst.i==move.dst.i)	&&
					(mptr->dst.j==move.dst.j)	){
				return true;
			}
		}
	}
	return false;
/*
	Node<Move *> *sptr;
	sptr=activePlayer->globalMoves->list.root;
	while(sptr->next){
		sptr=sptr->next;
		if(sptr->item->valid){
			if(	(sptr->item->src.i==move.src.i)	&&
					(sptr->item->src.j==move.src.j)	&&
					(sptr->item->dst.i==move.dst.i)	&&
					(sptr->item->dst.j==move.dst.j)	){
				return true;
			}
		}
	}
	return false;
*/
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
	//player->pieces->print();
	printPieces(player->pieces);
	printf("\ncaptured:");
	//player->captured->print();
	printPieces(player->captured);
	printf("\nlegalmoves:");
	printLegalMoves(player->globalMoves);
	//player->globalMoves->print();
	printf("\ninvalidated:");
	//player->globalMoves->list.apply(printInvalidated);
	printInvalidated(player->globalMoves);
	printf("\n((%d))",nLegalMoves(player));
	printf("\nkingSquare:");
	player->kingSquare->print();
	printf("\n");
	printMoveList();
//	board->whitePieces->print();
//	board->blackPieces->print();
	Piece *p;
	valid=false;
	while(!valid){
		player->decide(currentMove);
		if(currentMove.quit){
			running=false;
			return;
		}
		valid=isValidMove(currentMove);
		if(!valid){
			printf("invalid move.\n");
		}
#ifdef DEBUG
		valid=Rules::verify(player->color,board,currentMove);
		assert(valid);
#endif
	}
	player->promotedPawn=0;	//pawn may have been flagged during move validity testing.
	p=board->makeMove(currentMove,false);
	addToRecord(currentMove);
	if(player->isChecked()){
		printf("move cannot result in king being under attack.\n");
		assert(false);
	}
	if(p){
		player->captured->push_back(p);
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
	}else if(	(currentMove.src.j==4)											&&
						(currentMove.dst.j==6)											&&
						(player->kingSquare->j==6)									&&
						(currentMove.src.i==currentMove.dst.i)			&&
						(player->kingSquare->i==currentMove.dst.i)	){
		currentMove.src.j=7;
		currentMove.dst.j=5;
		board->makeMove(currentMove,false);
	}else if(	(currentMove.src.j==4)											&&
						(currentMove.dst.j==2)											&&
						(player->kingSquare->j==2)									&&
						(currentMove.src.i==currentMove.dst.i)			&&
						(player->kingSquare->i==currentMove.dst.i)	){
		currentMove.src.j=0;
		currentMove.dst.j=3;
		board->makeMove(currentMove,false);
	}else if(player->enPassant){
		if(	(currentMove.src.i==player->enPassant->square->i)		&&
				(currentMove.dst.j==player->enPassant->square->j)		&&
				(board->square[currentMove.dst.i][currentMove.dst.j].piece->type==PawnT)){
			player->enPassant->removePiece();
			board->display(1);
			player->enPassant=0;
		}
	}
	player->nextPlayer->updateGlobalMoves();
}
