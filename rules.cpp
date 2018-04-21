#include"rules.h"
bool Rules::verify(const enum Color &color,Board *board,const Move &move){
	Coord src=move.src;
	Coord dst=move.dst;
	int dx,dy,startingRank;
	Piece *p=board->square[src.i][src.j]->piece;
	if(p->color!=color){
		printf("Player must select piece of correct color.\n");
		return false;
	}
	bool capturing=false;
	switch(p->type){
		case(PawnT):
			if(p->color==White){
				dx=src.i-dst.i;
				startingRank=6;
			}else{
				dx=dst.i-src.i;
				startingRank=1;
			}
			dy=dst.j-src.j;
			if(dx==2){
				if(src.i!=startingRank){
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
