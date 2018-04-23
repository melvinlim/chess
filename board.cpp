#include"board.h"
Board::Board(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			square[i][j]=new Square(i,j,this);
		}
	}
	whitePieces=new Collection<Piece *>();
	blackPieces=new Collection<Piece *>();
}
Board::~Board(){}
void Board::placePiece(int i,int j,enum Color color,Piece *p){
	switch(color){
		case White:
			whitePieces->add(p);
			p->player=players[0];
		break;
		case Black:
			blackPieces->add(p);
			p->player=players[1];
		break;
	}
	square[i][j]->place(p);
	p->square=square[i][j];
}
void Board::placeSidePieces(int row,enum Color color){
	Piece *p;
	p=new Rook(color);
	placePiece(row,0,color,p);
	p=new Knight(color);
	placePiece(row,1,color,p);
	p=new Bishop(color);
	placePiece(row,2,color,p);
	p=new Rook(color);
	placePiece(row,7,color,p);
	p=new Knight(color);
	placePiece(row,6,color,p);
	p=new Bishop(color);
	placePiece(row,5,color,p);
}
void updatePieceHelper(Piece *piece){
	piece->threats->clear();
	piece->addThreats(piece->player->threats);
}
Piece *Board::move(Move &move,Collection<Square *> *threats){
	int i=move.src.i;
	int j=move.src.j;
	int di=move.dst.i;
	int dj=move.dst.j;
//	printf("moving %s at %d %d to %d %d\n",(square[i][j]->piece->self).data(),move.src.i,move.src.j,move.dst.i,move.dst.j);
	Piece *srcPiece=square[i][j]->piece;
	Piece *dstPiece=square[di][dj]->piece;
	threats->remove(srcPiece->threats);
	srcPiece->threats->clear();
	square[di][dj]->piece=square[i][j]->piece;
	square[i][j]->piece=0;
	srcPiece->square=square[di][dj];
	srcPiece->addThreats(threats);
	square[i][j]->threats->list.apply(updatePieceHelper);
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
	placeRowPieces(0,Black);
	placeRowPieces(7,White);
	placeSidePieces(0,Black);
	placeSidePieces(7,White);
}
void Board::placePawns(){
	placeRowPawns(1,Black);
	placeRowPawns(6,White);
}
void Board::reset(){
	delete whitePieces;
	delete blackPieces;
	whitePieces=new Collection<Piece *>();
	blackPieces=new Collection<Piece *>();
	placePawns();
	placePieces();
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
void Board::display(bool labels){
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
