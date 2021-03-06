#include"rules.h"
bool Rules::checked(const Board *board,const Player *player,const Square &dstSquare){
	int i,j;
	Move *mptr;
	int n=player->nextPlayer->globalMoves->size;
	for(int x=0;x<n;x++){
		mptr=player->nextPlayer->globalMoves->atIndex(x);
		i=mptr->dst.i;
		j=mptr->dst.j;
//		attackedSquare=&board->square[i][j];
		if(&board->square[i][j]==&dstSquare){
			return true;
		}
	}
	return false;
}
bool Rules::verifySrc(const Board *board,const Coord &coord){
	if(board->square[coord.i][coord.j].piece==0){
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
		if(dx==2){
			if(	(board->square[move.src.i][move.src.j].piece->hasMoved)	||
					(board->square[move.src.i][move.src.j+1].piece!=0)				||
					(board->square[move.src.i][move.src.j+2].piece!=0)				||
					(dy!=0)																										){
				printf("King can only move 1 square in any direction.\n");
				return false;
			}
		}else if(dx==-2){
			if(	(board->square[move.src.i][move.src.j].piece->hasMoved)	||
					(board->square[move.src.i][move.src.j-1].piece!=0)				||
					(board->square[move.src.i][move.src.j-2].piece!=0)				||
					(dy!=0)																										){
				printf("King can only move 1 square in any direction.\n");
				return false;
			}
		}else{
			printf("King can only move 1 square in any direction.\n");
			return false;
		}
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
			if(board->square[i][j].piece){
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
			if(board->square[i][j].piece){
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
			if(board->square[i][j].piece){
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
			if(board->square[src.i][j].piece){
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
			if(board->square[i][src.j].piece){
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
	Piece *p=board->square[src.i][src.j].piece;
	Piece *pAtDst=board->square[dst.i][dst.j].piece;
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
				if((src.i!=startingRank)||(dy!=0)){
						printf("pawns may move 2 squares only on their first move.\n");
						return false;
				}
				return true;
			}else if(dx==1){
				if(!capturing){
					if(dy!=0){
						printf("pawns may not move sideways unless capturing\n");
						Piece *pEnPassant=0;
						if(color==White)
							pEnPassant=board->square[dst.i+1][dst.j].piece;
						else
							pEnPassant=board->square[dst.i-1][dst.j].piece;
						if(pEnPassant->enPassant)
							return true;
						else
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
void Rules::addLegalMove(Stack<Move *> *allLegalMoves,const Square &src,const Square &dst){
	Move *move=new Move();
	move->piece=src.piece;
//	move->dstSquare=dst;
	move->src.i=src.i;
	move->src.j=src.j;
	move->dst.i=dst.i;
	move->dst.j=dst.j;
	allLegalMoves->push_back(move);
}
void Rules::updateMoveList(Stack<Move *> *allLegalMoves,const Square &src,const Square &dst){
	if((!dst.piece)||(dst.piece->player!=src.piece->player)){
		addLegalMove(allLegalMoves,src,dst);
	}
}
void Rules::addKingMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start){
	Square (*square)[8]=board->square;
	int si,sj;
	si=start->i;
	sj=start->j;
	if(sj>0){
		updateMoveList(allLegalMoves,*start,square[si][sj-1]);
		if(si>0){
			updateMoveList(allLegalMoves,*start,square[si-1][sj-1]);
		}
		if(si<7){
			updateMoveList(allLegalMoves,*start,square[si+1][sj-1]);
		}
	}
	if(sj<7){
		updateMoveList(allLegalMoves,*start,square[si][sj+1]);
		if(si>0){
			updateMoveList(allLegalMoves,*start,square[si-1][sj+1]);
		}
		if(si<7){
			updateMoveList(allLegalMoves,*start,square[si+1][sj+1]);
		}
	}
	if(si>0){
		updateMoveList(allLegalMoves,*start,square[si-1][sj]);
	}
	if(si<7){
		updateMoveList(allLegalMoves,*start,square[si+1][sj]);
	}
	if(!start->piece->hasMoved){
		if(square[si][sj+1].piece==0){
			if(!checked(board,start->piece->player,square[si][sj+1])){
				if(square[si][sj+2].piece==0){
					if(!checked(board,start->piece->player,square[si][sj+2])){
						if((square[si][sj+3].piece)&&(!square[si][sj+3].piece->hasMoved)){
							updateMoveList(allLegalMoves,*start,square[si][sj+2]);
						}
					}
				}
			}
		}
		if(square[si][sj-1].piece==0){
			if(!checked(board,start->piece->player,square[si][sj-1])){
				if(square[si][sj-2].piece==0){
					if(square[si][sj-3].piece==0){
						if(!checked(board,start->piece->player,square[si][sj-2])){
							if((square[si][sj-4].piece)&&(!square[si][sj-4].piece->hasMoved)){
								updateMoveList(allLegalMoves,*start,square[si][sj-2]);
							}
						}
					}
				}
			}
		}
	}
}
void Rules::addQueenMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start){
	addRookMoves(board,allLegalMoves,start);
	addBishopMoves(board,allLegalMoves,start);
}
void Rules::addBishopMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start){
	Square (*square)[8]=board->square;
	int si,sj,i,j;
	si=start->i;
	sj=start->j;
	i=si+1;
	j=sj+1;
	while(i<=7&&j<=7){
		updateMoveList(allLegalMoves,*start,square[i][j]);
		if(square[i++][j++].piece){
			break;
		}
	}
	i=si-1;
	j=sj-1;
	while(i>=0&&j>=0){
		updateMoveList(allLegalMoves,*start,square[i][j]);
		if(square[i--][j--].piece){
			break;
		}
	}
	i=si+1;
	j=sj-1;
	while(i<=7&&j>=0){
		updateMoveList(allLegalMoves,*start,square[i][j]);
		if(square[i++][j--].piece){
			break;
		}
	}
	i=si-1;
	j=sj+1;
	while(i>=0&&j<=7){
		updateMoveList(allLegalMoves,*start,square[i][j]);
		if(square[i--][j++].piece){
			break;
		}
	}
}
void Rules::addKnightMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start){
	//Square *(*square)[8]=board->square;
	Square (*square)[8]=board->square;
	int si,sj;
	si=start->i;
	sj=start->j;
	if(sj>1){
		if(si>0){
			updateMoveList(allLegalMoves,*start,square[si-1][sj-2]);
		}
		if(si<7){
			updateMoveList(allLegalMoves,*start,square[si+1][sj-2]);
		}
	}
	if(sj<6){
		if(si>0){
			updateMoveList(allLegalMoves,*start,square[si-1][sj+2]);
		}
		if(si<7){
			updateMoveList(allLegalMoves,*start,square[si+1][sj+2]);
		}
	}
	if(si>1){
		if(sj>0){
			updateMoveList(allLegalMoves,*start,square[si-2][sj-1]);
		}
		if(sj<7){
			updateMoveList(allLegalMoves,*start,square[si-2][sj+1]);
		}
	}
	if(si<6){
		if(sj>0){
			updateMoveList(allLegalMoves,*start,square[si+2][sj-1]);
		}
		if(sj<7){
			updateMoveList(allLegalMoves,*start,square[si+2][sj+1]);
		}
	}
}
void Rules::addRookMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start){
//	Square *(*square)[8]=board->square;
	Square (*square)[8]=board->square;
	int si,sj,i,j;
	si=start->i;
	sj=start->j;
	for(j=sj+1;j<=7;j++){
		updateMoveList(allLegalMoves,*start,square[si][j]);
		if(square[si][j].piece){
			break;
		}
	}
	for(j=sj-1;j>=0;j--){
		updateMoveList(allLegalMoves,*start,square[si][j]);
		if(square[si][j].piece){
			break;
		}
	}
	for(i=si+1;i<=7;i++){
		updateMoveList(allLegalMoves,*start,square[i][sj]);
		if(square[i][sj].piece){
			break;
		}
	}
	for(i=si-1;i>=0;i--){
		updateMoveList(allLegalMoves,*start,square[i][sj]);
		if(square[i][sj].piece){
			break;
		}
	}
}
void Rules::addPawnMoves(Board *board,Stack<Move *> *allLegalMoves,Square *start,int forwardDirection){
	Square *square;
	int forwardSquare=start->i+forwardDirection;
	if((forwardSquare>7)||(forwardSquare<0))	return;
	if(start->j>0){
		square=&board->square[forwardSquare][start->j-1];
		if(square->piece&&(square->piece->player!=start->piece->player)){
			addLegalMove(allLegalMoves,*start,*square);
		}
	}
	if(start->j<7){
		square=&board->square[forwardSquare][start->j+1];
		if(square->piece&&(square->piece->player!=start->piece->player)){
			addLegalMove(allLegalMoves,*start,*square);
		}
	}
	square=&board->square[forwardSquare][start->j];
	if(!square->piece){
		addLegalMove(allLegalMoves,*start,*square);
	}
	if(!start->piece->hasMoved){
		if(start->i==1){
			square=&board->square[3][start->j];
			if(!square->piece){
				addLegalMove(allLegalMoves,*start,*square);
			}
		}else if(start->i==6){
			square=&board->square[4][start->j];
			if(!square->piece){
				addLegalMove(allLegalMoves,*start,*square);
			}
		}
	}
	Player *currentPlayer=start->piece->player;
	if((start->i==3)&&(start->piece->player->color==White)){
		Move *previousMove=currentPlayer->nextPlayer->previousMove;
		Piece *previousPiece=board->square[previousMove->dst.i][previousMove->dst.j].piece;
		if(	(previousPiece)	&&
				(previousPiece->type==PawnT)	&&
				(abs(previousMove->dst.j-start->j)==1)	&&
				(previousMove->dst.i==3)	&&
				(previousMove->src.i==1)	){
			square=&board->square[forwardSquare][previousMove->dst.j];
			addLegalMove(allLegalMoves,*start,*square);
			currentPlayer->enPassant=previousPiece;
			previousPiece->enPassant=true;
		}
	}else if((start->i==4)&&(start->piece->player->color==Black)){
		Move *previousMove=currentPlayer->nextPlayer->previousMove;
		Piece *previousPiece=board->square[previousMove->dst.i][previousMove->dst.j].piece;
		if(	(previousPiece)	&&
				(previousPiece->type==PawnT)	&&
				(abs(previousMove->dst.j-start->j)==1)	&&
				(previousMove->dst.i==4)	&&
				(previousMove->src.i==6)	){
			square=&board->square[forwardSquare][previousMove->dst.j];
			addLegalMove(allLegalMoves,*start,*square);
			currentPlayer->enPassant=previousPiece;
			previousPiece->enPassant=true;
		}
	}
}
