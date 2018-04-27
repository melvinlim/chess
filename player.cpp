#include"player.h"
void helperFunc(Piece *p){
	p->addThreats(p->player->threats);
}
Player::Player(enum Color c,Board *board){
	color=c;
	if(color==White){
		strcpy(colorStr,"White");
		this->pieces=board->whitePieces;
	}else{
		strcpy(colorStr,"Black");
		this->pieces=board->blackPieces;
	}
	this->captured=new Collection<Piece *>();
	this->threats=new Collection<Square *>();
	this->legalMoves=new Collection<Square *>();
	this->board=board;
	result=Playing;
/*
	for(auto it=pieces->list.begin();it!=pieces->list.end();it++){
		(*it)->addThreats(threats);
	}
*/
}
void Player::initThreatsList(){
	pieces->list.apply(helperFunc);
}
Random::Random(enum Color c,Board *board):Player(c,board){}
void Random::decide(Move &move){
	srand(time(0));
	Piece *chosenPiece;
	Square *dstSquare;
again:
	do{	//this is potentially very inefficient.
		chosenPiece=pieces->randomElement();
	}while(chosenPiece->legalMoves->list.size==0);
	dstSquare=chosenPiece->legalMoves->randomElement();
	if(!dstSquare->valid)	goto again;
	move.src.i=chosenPiece->square->i;
	move.src.j=chosenPiece->square->j;
	move.dst.i=dstSquare->i;
	move.dst.j=dstSquare->j;
}
Human::Human(enum Color c,Board *board):Player(c,board){}
int Human::getCoord(string type,Move &move){
	cin>>str;
	if((str.size()==1)&&((str[0]=='q')||(str[0]=='Q'))){
		move.quit=true;
		return 0;
	}
	int npart=str[1]-48;
	char apart=tolower(str[0]);
	if((str.size()!=2)||(apart<'a')||(apart>'h')||(npart<1)||(npart>8)){
		printf("%s must be a letter from A-H followed by a number from 1-8.\n",type.data());
		return -1;
	}
	if(type[0]=='s'){
		strncpy(move.src.str,str.data(),2);
		Utility::stringToCoord(str,move.src);
		if(!Rules::verifySrc(board,move.src)){
			return -1;
		}
	}else{
		strncpy(move.dst.str,str.data(),2);
		Utility::stringToCoord(str,move.dst);
	}
	return 0;
}
void Human::decide(Move &move){
	printf("%s:",colorStr);
	while((getCoord("starting square",move))<0);
	if(move.quit)	return;
	printf("%s:",colorStr);
	while((getCoord("ending square",move))<0);
	if(move.quit)	return;
}
