#include"player.h"
Player::Player(enum Color c,Board *board){
	color=c;
	this->board=board;
}
Human::Human(enum Color c,Board *board):Player(c,board){}
int Human::getCoord(string type,Move &move){
	Square *square;
	printf(":");
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
		utility.coordToSquare(str,move.src);
		square=board->square[move.src.i][move.src.j];
		if(square->piece==0){
			printf("%s must be occupied.\n",type.data());
			return -1;
		}
	}else{
		strncpy(move.dst.str,str.data(),2);
		utility.coordToSquare(str,move.dst);
		square=board->square[move.dst.i][move.dst.j];
		if(square->piece!=0){
			//printf("%x\n",square->piece);
//			square->piece->display();
			printf("%s must be vacant.\n",type.data());
			return -1;
		}
	}
	return 0;
}
void Human::decide(Move &move){
	while((getCoord("starting square",move))<0);
	if(move.quit)	return;
	while((getCoord("ending square",move))<0);
	if(move.quit)	return;
}
