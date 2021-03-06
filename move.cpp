#include"move.h"
Move::Move(){
	valid=true;
	piece=0;
}
Move::Move(const Move &move){
	valid=move.valid;
	piece=move.piece;
	this->src=move.src;
	this->dst=move.dst;
}
Move::Move(const struct Coord &src,const struct Coord &dst){
	valid=true;
	piece=0;
	this->src=src;
	this->dst=dst;
}
Move::Move(const int &srci,const int &srcj,const int &dsti,const int &dstj){
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
