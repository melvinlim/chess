#include"player.h"
Player::Player(enum Color c){
	color=c;
}
Human::Human(enum Color c):Player(c){}
bool Human::decide(Move &move){
	return true;
}
