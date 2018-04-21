#include"player.h"
Player::Player(enum Color c,Board *board){
	color=c;
	this->board=board;
}
Human::Human(enum Color c,Board *board):Player(c,board){}
bool Human::decide(Move &move){
	return true;
}
