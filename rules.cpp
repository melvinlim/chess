#include"rules.h"
bool Rules::verify(const enum Color &color,Board *board,const Move &move){
	Coord src=move.src;
	Coord dst=move.dst;
	int dx,dy;
	Piece *p=board->square[src.i][src.j]->piece;
	if(p->color!=color){
		printf("Player must select piece of correct color.\n");
		return false;
	}
	bool capturing=false;
	switch(p->type){
		case(PawnT):
			dy=dst.j-src.j;
			if(p->color==White){
				dx=src.i-dst.i;
				if(dx==2){
					if(src.i!=6){
						printf("pawns may move 2 squares only on their first move.\n");
						return false;
					}
				}else if(dx==1){
					if(!capturing){
						if(dy!=0){
							printf("pawns may not move sideways unless capturing\n");
							return false;
						}
					}else{
						if(abs(dy)!=1){
							printf("pawns must move exactly one square left/right when capturing.\n");
							return false;
						}
					}
				}else{
					printf("pawns may only move one square forward\n");
					return false;
				}
			}else{
			}
		break;
		case(KnightT):
		break;
		case(BishopT):
		break;
		case(RookT):
		break;
		case(QueenT):
		break;
		case(KingT):
		break;
	}
	return true;
}
