#include"collection.h"
void Collection::add(Piece *piece){
	list.push_front(piece);
}
void Collection::remove(Piece *piece){
	list.remove(piece);
}
void Collection::print(){
	for(Piece *p:list)	p->display();
}
