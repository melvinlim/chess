#include"move.h"
Move::Move(){
	valid=true;
	piece=0;
}
Move::Move(int srci,int srcj,int dsti,int dstj){
	valid=true;
	piece=0;
	src.i=srci;
	src.j=srcj;
	dst.i=dsti;
	dst.j=dstj;
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
Move::~Move(){
}
