#include"player.h"
void updatePieceHelper(Piece *piece){
	if(piece->removed)	return;
	piece->addMoves();
}
void Player::updateGlobalMoves(){
	delete globalMoves;
	globalMoves=new Stack<Move *>(MAXMOVESZ);
//	globalMoves->clear();
	for(auto it=pieces->begin();it!=pieces->end();it++){
		updatePieceHelper(*it);
	}
//	pieces->list.apply(updatePieceHelper);
}
bool Player::isChecked(){
	nextPlayer->updateGlobalMoves();
	return Rules::checked(this,*kingSquare);
}
void Player::reset(){
	previousMove=0;
	promotedPawn=0;
	enPassant=0;
	Piece *p;
	for(auto it=captured->begin();it!=captured->end();it++){
		p=*it;
		delete p;
	}
	captured->clear();
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
	this->captured=new std::list<Piece *>();
	//this->captured=new Collection<Piece *>();
	//this->globalMoves=new Collection<Move *>();
	this->globalMoves=new Stack<Move *>(MAXMOVESZ);
	this->board=board;
	result=Playing;
	promotedPawn=0;
	previousMove=0;
	enPassant=0;
}
Random::Random(enum Color c,Board *board):Player(c,board){}
void Random::decide(Move &move){
	Move *chosenMove;
	srand(time(0));
	int n=globalMoves->size;
	int i=random()%n;
	//chosenMove=globalMoves->randomElement();
	chosenMove=globalMoves->atIndex(i);
	while(!chosenMove->valid){
		i++;
		i=i%n;
		chosenMove=globalMoves->atIndex(i);
//		chosenMove=globalMoves->nextElement();
	}
	move.src.i=chosenMove->src.i;
	move.src.j=chosenMove->src.j;
	move.dst.i=chosenMove->dst.i;
	move.dst.j=chosenMove->dst.j;
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
	char srcbuf[3];
	char dstbuf[3];
	if(type[0]=='s'){
		strncpy(srcbuf,str.data(),2);
		Utility::stringToCoord(str,move.src);
		if(!Rules::verifySrc(move.src)){
			return -1;
		}
	}else{
		strncpy(dstbuf,str.data(),2);
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
