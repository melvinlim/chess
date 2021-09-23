#include"utility.h"
void Utility::stringToCoord(const std::string s,Coord &coord){
	int j=toupper(s[0])-65;
	int i=7-(s[1]-49);
	printf("%s -> %d %d\n",s.data(),i,j);
	coord.i=i;
	coord.j=j;
}
void Utility::coordToString(char *s,const Coord &coord){
	s[0]=coord.j+65;
	s[1]=(7-coord.i)+49;
	s[2]=0;
}
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
void Move::print(){
  char buf1[256];
  char buf2[256];
  Utility::coordToString(buf1,src);
  Utility::coordToString(buf2,dst);
  //    printf("(%d,%d)->(%d,%d) ",src.i,src.j,dst.i,dst.j);
  printf(" %s->%s",buf1,buf2);
}
