#include"board.h"
Board::Board(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			square[i][j]=new Square(i,j);
		}
	}
	whitePieces=new std::list<Piece *>();
	blackPieces=new std::list<Piece *>();
}
Board::~Board(){}
void removeAllHelper(Piece *p){
	p->removePiece();
}
void Board::removeAllPieces(){
	Piece *p;
	for(auto it=whitePieces->begin();it!=whitePieces->end();it++){
		p=*it;
		removeAllHelper(p);
		delete p;
	}
	for(auto it=blackPieces->begin();it!=blackPieces->end();it++){
		p=*it;
		removeAllHelper(p);
		delete p;
	}
//	whitePieces->list.apply(removeAllHelper);
//	blackPieces->list.apply(removeAllHelper);
//	whitePieces->deepClear();
//	blackPieces->deepClear();
	delete whitePieces;
	delete blackPieces;
	whitePieces=new std::list<Piece *>();
	blackPieces=new std::list<Piece *>();
}
void Board::placePiece(int i,int j,enum Color color,Piece *p){
	switch(color){
		case White:
			whitePieces->push_back(p);
			p->player=players[0];
		break;
		case Black:
			blackPieces->push_back(p);
			p->player=players[1];
		break;
		default:
			assert(false);
	}
	square[i][j]->place(p);
	p->place(square[i][j]);
}
void Board::placeSidePieces(int row,enum Color color){
	Piece *p;
	p=new Rook(color);
	placePiece(row,0,color,p);
	p=new Knight(color);
	placePiece(row,1,color,p);
	p=new Knight(color);
	placePiece(row,6,color,p);
	p=new Bishop(color);
	placePiece(row,2,color,p);
	p=new Bishop(color);
	placePiece(row,5,color,p);
	p=new Rook(color);
	placePiece(row,7,color,p);
}
Piece *Board::makeMove(const Move &move,const bool testMove){
	int i=move.src.i;
	int j=move.src.j;
	int di=move.dst.i;
	int dj=move.dst.j;
	Square *srcSquare=square[i][j];
	Square *dstSquare=square[di][dj];
//	printf("moving %s at %d %d to %d %d\n",(square[i][j]->piece->self).data(),move.src.i,move.src.j,move.dst.i,move.dst.j);
	Piece *srcPiece=srcSquare->piece;
	Piece *dstPiece=dstSquare->piece;
	if(dstPiece)	dstPiece->removePiece();
	srcPiece->removePiece();
	srcPiece->place(dstSquare);
	if(!testMove)	srcPiece->hasMoved=true;
	return dstPiece;
}
void Board::placeRowPieces(int row,enum Color color){
	Piece *p;
	p=new King(color);
	placePiece(row,4,color,p);
	p=new Queen(color);
	placePiece(row,3,color,p);
}
void Board::placeRowPawns(int row,enum Color color){
	Piece *p;
	for(int j=0;j<8;j++){
		p=new Pawn(color);
		placePiece(row,j,color,p);
		//assert(square[row][j]->id==p->square->id);
	}
}
void Board::placePieces(){
	placeSidePieces(0,Black);
	placeSidePieces(7,White);
	placeRowPieces(0,Black);
	placeRowPieces(7,White);
}
void Board::placePawns(){
	placeRowPawns(1,Black);
	placeRowPawns(6,White);
}
void Board::placeAllPieces(){
	placePawns();
	placePieces();
	players[0]->updateGlobalMoves();
	players[1]->updateGlobalMoves();
}
void Board::debug(){
	printf("+--+--+--+--+--+--+--+--+\n");
	for(int i=0;i<8;i++){
		printf("|");
		for(int j=0;j<8;j++){
			printf("%s",square[i][j]->strId.data());
			printf("|");
		}
		printf("\n+--+--+--+--+--+--+--+--+\n");
	}
}
void Board::display(const bool labels){
	if(labels)	printf("  ");
	printf("+--+--+--+--+--+--+--+--+\n");
	for(int i=0;i<8;i++){
		if(labels)	printf("%c ",(7-i)+48+1);
		printf("|");
		for(int j=0;j<8;j++){
			square[i][j]->display();
			printf("|");
		}
		printf("\n");
		if(labels)	printf("  ");
		printf("+--+--+--+--+--+--+--+--+\n");
	}
	if(labels)	printf("    A  B  C  D  E  F  G  H\n");
}
