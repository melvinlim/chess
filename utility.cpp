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
}
Move::Move(){
	valid=true;
}
Move::Move(Move *item){
	valid=true;
	src=item->src;
	dst=item->dst;
}
