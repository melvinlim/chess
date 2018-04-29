#include"rules.h"
bool Rules::checked(const Player *player){
	int i,j;
	Square *attackedSquare;
	Node<Move *> *ptr=player->nextPlayer->globalMoves->list.root;
	while(ptr->next){
		ptr=ptr->next;
		i=ptr->item->dst.i;
		j=ptr->item->dst.j;
		attackedSquare=player->board->square[i][j];
		if(attackedSquare==player->kingSquare){
			return true;
		}
	}
	return false;
}
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
bool Rules::verifyKnight(const Board *board,const Move &move){
	int adx,ady;
	Coord src=move.src;
	Coord dst=move.dst;
	adx=abs(dst.j-src.j);
	ady=abs(dst.i-src.i);
	if(((adx==2)&&(ady==1))||((adx==1)&&(ady==2)))	return true;
	printf("knights move one square straight and one square diagonally\n");
	return false;
}
bool Rules::verifyKing(const Board *board,const Move &move){
	int dx,dy;
	Coord src=move.src;
	Coord dst=move.dst;
	dx=dst.j-src.j;
	dy=dst.i-src.i;
	if((abs(dx)>1)||(abs(dy)>1)){
		printf("King can only move 1 square in any direction.\n");
		return false;
	}
	return true;
}
bool Rules::verifyQueen(const Board *board,const Move &move){
	if(verifyRook(board,move))	return true;
	if(verifyBishop(board,move))	return true;
	return false;
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
			return verifyKnight(board,move);
		break;
		case(BishopT):
			return verifyBishop(board,move);
		break;
		case(RookT):
			return verifyRook(board,move);
		break;
		case(QueenT):
			return verifyQueen(board,move);
		break;
		case(KingT):
			return verifyKing(board,move);
		break;
	}
	return true;
}
void Rules::addBothLegalMoves(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Square *src,Square *dst){
	Move *move=new Move();
	move->piece=src->piece;
	move->dstSquare=dst;
	move->src.i=src->i;
	move->src.j=src->j;
	move->dst.i=dst->i;
	move->dst.j=dst->j;
	allLegalMoves->add(move);
//	localLegalMoves->add(move);
}
void Rules::updateAllLists(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *src,Square *dst){
	if((!dst->piece)||(dst->piece->player!=src->piece->player)){
		addBothLegalMoves(allLegalMoves,localLegalMoves,src,dst);
	}
	addBothThreats(allThreats,localThreats,src,dst);
}
void Rules::addBothThreats(Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *src,Square *dst){
}
void Rules::addKingThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start){
	Square *(*square)[8]=start->board->square;
	int si,sj;
	si=start->i;
	sj=start->j;
	if(sj>0){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si][sj-1]);
		if(si>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-1][sj-1]);
		}
		if(si<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+1][sj-1]);
		}
	}
	if(sj<7){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si][sj+1]);
		if(si>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-1][sj+1]);
		}
		if(si<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+1][sj+1]);
		}
	}
	if(si>0){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-1][sj]);
	}
	if(si<7){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+1][sj]);
	}
}
void Rules::addQueenThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start){
	addRookThreats(allLegalMoves,localLegalMoves,allThreats,localThreats,start);
	addBishopThreats(allLegalMoves,localLegalMoves,allThreats,localThreats,start);
}
void Rules::addBishopThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start){
	Square *(*square)[8]=start->board->square;
	int si,sj,i,j;
	si=start->i;
	sj=start->j;
	i=si+1;
	j=sj+1;
	while(i<=7&&j<=7){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][j]);
		if(square[i++][j++]->piece){
			break;
		}
	}
	i=si-1;
	j=sj-1;
	while(i>=0&&j>=0){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][j]);
		if(square[i--][j--]->piece){
			break;
		}
	}
	i=si+1;
	j=sj-1;
	while(i<=7&&j>=0){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][j]);
		if(square[i++][j--]->piece){
			break;
		}
	}
	i=si-1;
	j=sj+1;
	while(i>=0&&j<=7){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][j]);
		if(square[i--][j++]->piece){
			break;
		}
	}
}
void Rules::addKnightThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start){
	Square *(*square)[8]=start->board->square;
	int si,sj;
	si=start->i;
	sj=start->j;
	if(sj>1){
		if(si>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-1][sj-2]);
		}
		if(si<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+1][sj-2]);
		}
	}
	if(sj<6){
		if(si>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-1][sj+2]);
		}
		if(si<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+1][sj+2]);
		}
	}
	if(si>1){
		if(sj>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-2][sj-1]);
		}
		if(sj<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si-2][sj+1]);
		}
	}
	if(si<6){
		if(sj>0){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+2][sj-1]);
		}
		if(sj<7){
			updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si+2][sj+1]);
		}
	}
}
void Rules::addRookThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start){
	Square *(*square)[8]=start->board->square;
	int si,sj,i,j;
	si=start->i;
	sj=start->j;
	for(j=sj+1;j<=7;j++){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si][j]);
		if(square[si][j]->piece){
			break;
		}
	}
	for(j=sj-1;j>=0;j--){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[si][j]);
		if(square[si][j]->piece){
			break;
		}
	}
	for(i=si+1;i<=7;i++){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][sj]);
		if(square[i][sj]->piece){
			break;
		}
	}
	for(i=si-1;i>=0;i--){
		updateAllLists(allLegalMoves,localLegalMoves,allThreats,localThreats,start,square[i][sj]);
		if(square[i][sj]->piece){
			break;
		}
	}
}
void Rules::addPawnThreats(Collection<Move *> *allLegalMoves,Collection<Move *> *localLegalMoves,Collection<Move *> *allThreats,Collection<Move *> *localThreats,Square *start,int forwardDirection){
	Board *board=start->board;
	Square *square;
	int forwardSquare=start->i+forwardDirection;
	if((forwardSquare>7)||(forwardSquare<0))	return;
	if(start->j>0){
		square=board->square[forwardSquare][start->j-1];
		if(square->piece&&(square->piece->player!=start->piece->player)){
			addBothLegalMoves(allLegalMoves,localLegalMoves,start,square);
		}
		addBothThreats(allThreats,localThreats,start,square);
	}
	if(start->j<7){
		square=board->square[forwardSquare][start->j+1];
		if(square->piece&&(square->piece->player!=start->piece->player)){
			addBothLegalMoves(allLegalMoves,localLegalMoves,start,square);
		}
		addBothThreats(allThreats,localThreats,start,square);
	}
	square=board->square[forwardSquare][start->j];
	if(!square->piece){
		addBothLegalMoves(allLegalMoves,localLegalMoves,start,square);
	}
	if(!start->piece->hasMoved){
		start->piece->hasMoved=true;
		if(start->i==1){
			square=board->square[3][start->j];
		}
		if(start->i==6){
			square=board->square[4][start->j];
		}
		addBothLegalMoves(allLegalMoves,localLegalMoves,start,square);
	}
}
