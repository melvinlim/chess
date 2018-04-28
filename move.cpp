#include"move.h"
Move::Move(){
	valid=true;
}
Move::Move(Move *item){
	valid=true;
	src=item->src;
	dst=item->dst;
}
