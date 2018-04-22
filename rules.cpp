#include"rules.h"
bool Rules::verifySrc(const Board *board,const Coord &coord){
	if(board->square[coord.i][coord.j]->piece==0){
		printf("starting square must be occupied\n");
		return false;
	}
	return true;
}
bool Rules::verifyColor(const Piece *p,const enum Color &color){
	if(p->color!=color){
		printf("Player must select piece of correct color.\n");
		return false;
	}
	return true;
}
bool Rules::verifyBishop(const Board *board,const Move &move){
	int dx,dy;
	Coord src=move.src;
	Coord dst=move.dst;
	dx=dst.j-src.j;
	dy=dst.i-src.i;
	if(abs(dx)!=abs(dy)){
		printf("bishops move diagonally.\n");
		return false;
	}
	int xStart,xEnd;
	int yStart,yEnd;
	if(src.j>dst.j){
		xStart=dst.j;
		xEnd=src.j;
	}else{
		xStart=src.j;
		xEnd=dst.j;
	}
	if(src.i>dst.i){
		yStart=dst.i;
		yEnd=src.i;
	}else{
		yStart=src.i;
		yEnd=dst.i;
	}
	if(((dx>0)&&(dy>0))||((dx<0)&&(dy<0))){
		int i=yStart+1;
		int j=xStart+1;
		while(i<yEnd){
			if(board->square[i][j]->piece){
				printf("Bishops cannot jump over other pieces.  (1)\n");
				return false;
			}
			i++;
			j++;
		}
	}else if((dx>0)&&(dy<0)){
		int i=src.i-1;
		int j=src.j+1;
		while(j<dst.j){
			if(board->square[i][j]->piece){
				printf("Bishops cannot jump over other pieces.  (%d,%d) (2)\n",i,j);
				return false;
			}
			i--;
			j++;
		}
	}else{
		int i=src.i+1;
		int j=src.j-1;
		while(i<dst.i){
			if(board->square[i][j]->piece){
				printf("Bishops cannot jump over other pieces.  (%d,%d) (3)\n",i,j);
				return false;
			}
			i++;
			j--;
		}
	}
	return true;
}
bool Rules::verifyRook(const Board *board,const Move &move){
	bool lrMove,udMove;
	Coord src=move.src;
	Coord dst=move.dst;
	if(dst.i!=src.i)
		udMove=true;
	else
		udMove=false;
	if(dst.j!=src.j)
		lrMove=true;
	else
		lrMove=false;
	if((lrMove&&udMove)||(!lrMove&&!udMove)){
		printf("Rooks move horizontally or vertically.\n");
		return false;
	}
	int start,end;
	if(lrMove){
		if(src.j>dst.j){
			start=dst.j;
			end=src.j;
		}else{
			start=src.j;
			end=dst.j;
		}
		for(int j=start+1;j<end;j++){
			if(board->square[src.i][j]->piece){
				printf("Rooks cannot jump over other pieces.\n");
				return false;
			}
		}
	}else if(udMove){
		if(src.i>dst.i){
			start=dst.i;
			end=src.i;
		}else{
			start=src.i;
			end=dst.i;
		}
		for(int i=start+1;i<end;i++){
			if(board->square[i][src.j]->piece){
				printf("Rooks cannot jump over other pieces.\n");
				return false;
			}
		}
	}
	return true;
}
bool Rules::verify(const enum Color &color,const Board *board,const Move &move){
	Coord src=move.src;
	Coord dst=move.dst;
	int dx,dy,startingRank;
	Piece *p=board->square[src.i][src.j]->piece;
	Piece *pAtDst=board->square[dst.i][dst.j]->piece;
	if(!verifyColor(p,color))	return false;
	bool capturing;
	if(pAtDst){
		if(pAtDst->color==p->color){
			printf("cannot capture own piece.\n");
			return false;
		}
		capturing=true;
	}else{
		capturing=false;
	}
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
			return verifyBishop(board,move);
		break;
		case(RookT):
			return verifyRook(board,move);
		break;
		case(QueenT):
		break;
		case(KingT):
		break;
	}
	return true;
}
