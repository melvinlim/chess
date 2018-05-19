#include"piece.h"
using namespace std;
void Piece::removePiece(){
	if(enPassant){
		enPassant=0;
		player->nextPlayer->enPassant=0;
	}
	removed=true;
	if(square->piece==this){
		square->piece=0;
	}
}
void Piece::place(Square *targetSquare){
	removed=false;
	square=targetSquare;
	square->piece=this;
}
Piece::Piece(Color color){
	this->color=color;
	if(color==White){
		forwardDirection=-1;
	}else{
		forwardDirection=1;
	}
	removed=false;
	hasMoved=false;
	enPassant=false;
}
void Piece::display(){
	printf("%s",self.data());
}
void Piece::setSelf(string s){
	self=s;
	if(color==Black){
		self[1]+=32;
	}
}
void King::place(Square *targetSquare){
	Piece::place(targetSquare);
	player->kingSquare=targetSquare;
}
void Pawn::place(Square *targetSquare){
	Piece::place(targetSquare);
	if((targetSquare->i==0)||(targetSquare->i==7)){
		player->promotedPawn=this;
	}
}
King::King(Color color):Piece(color){
	setSelf(" K");
	type=KingT;
}
Pawn::Pawn(Color color):Piece(color){
	setSelf(" P");
	type=PawnT;
}
Queen::Queen(Color color):Piece(color){
	setSelf(" Q");
	type=QueenT;
}
Knight::Knight(Color color):Piece(color){
	setSelf(" N");
	type=KnightT;
}
Bishop::Bishop(Color color):Piece(color){
	setSelf(" B");
	type=BishopT;
}
Rook::Rook(Color color):Piece(color){
	setSelf(" R");
	type=RookT;
}
void Pawn::addMoves(){
	Rules::addPawnMoves(player->globalMoves,square,forwardDirection);
}
void King::addMoves(){
	Rules::addKingMoves(player->globalMoves,square);
}
void Queen::addMoves(){
	Rules::addQueenMoves(player->globalMoves,square);
}
void Knight::addMoves(){
	Rules::addKnightMoves(player->globalMoves,square);
}
void Bishop::addMoves(){
	Rules::addBishopMoves(player->globalMoves,square);
}
void Rook::addMoves(){
	Rules::addRookMoves(player->globalMoves,square);
}
void Piece::print(){
	display();
}
