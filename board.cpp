#include"board.h"
Board::Board(){
	int id=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			square[i][j]=new Square(id++);
		}
	}
}
Board::~Board(){}
void Board::placePiece(int i,int j,enum Color color,Piece *p){
	switch(color){
		case White:
			whitePieces.add(p);
		break;
		case Black:
			blackPieces.add(p);
		break;
	}
	square[i][j]->place(p);
}
void Board::placeSidePieces(int row,enum Color color){
	Piece *p;
	p=new Rook(color);
	placePiece(row,0,color,p);
//	square[row][0]->place(p);
	p=new Knight(color);
	square[row][1]->place(p);
	p=new Bishop(color);
	square[row][2]->place(p);
	p=new Rook(color);
	square[row][7]->place(p);
	p=new Knight(color);
	square[row][6]->place(p);
	p=new Bishop(color);
	square[row][5]->place(p);
}
void Board::move(Move &move){
	int i=move.src.i;
	int j=move.src.j;
	int di=move.dst.i;
	int dj=move.dst.j;
//	printf("moving %s at %d %d to %d %d\n",(square[i][j]->piece->self).data(),move.src.i,move.src.j,move.dst.i,move.dst.j);
	square[di][dj]->piece=square[i][j]->piece;
	square[i][j]->piece=0;
}
void Board::placeRowPieces(int row,enum Color color){
	Piece *p;
	p=new King(color);
	square[row][4]->place(p);
	p=new Queen(color);
	square[row][3]->place(p);
}
void Board::placeRowPawns(int row,enum Color color){
	Piece *p;
	for(int j=0;j<8;j++){
		p=new Pawn(color);
		square[row][j]->place(p);
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
