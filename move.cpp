#include"move.h"
Move::Move(){
	valid=true;
	piece=0;
}
Move::Move(Piece *piece){
	valid=true;
	this->piece=piece;
	assert(piece!=0);
}
Move::Move(Move *item){
	valid=true;
	piece=0;
	src=item->src;
	dst=item->dst;
}
