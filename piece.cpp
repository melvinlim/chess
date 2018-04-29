#include"piece.h"
using namespace std;
void Piece::removePiece(){
	removed=true;
	player->globalMoves->remove(localMoves);
	if(square->piece==this){
		square->piece=0;
	}
	delete localMoves;
	localMoves=new Collection<Move *>(this);
}
void Piece::place(Square *targetSquare){
	removed=false;
	square=targetSquare;
	square->piece=this;
	addThreats(this->player->globalMoves);
}
Piece::Piece(Color color){
	this->color=color;
	if(color==White){
		forwardDirection=-1;
	}else{
		forwardDirection=1;
	}
	localMoves=new Collection<Move *>(this);
	removed=false;
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
void Pawn::addThreats(Collection<Move *> *allThreats){
	Rules::addPawnThreats(player->globalMoves,localMoves,0,0,square,forwardDirection);
}
void King::addThreats(Collection<Move *> *allThreats){
	Rules::addKingThreats(player->globalMoves,localMoves,0,0,square);
}
void Queen::addThreats(Collection<Move *> *allThreats){
	Rules::addQueenThreats(player->globalMoves,localMoves,0,0,square);
}
void Knight::addThreats(Collection<Move *> *allThreats){
	Rules::addKnightThreats(player->globalMoves,localMoves,0,0,square);
}
void Bishop::addThreats(Collection<Move *> *allThreats){
	Rules::addBishopThreats(player->globalMoves,localMoves,0,0,square);
}
void Rook::addThreats(Collection<Move *> *allThreats){
	Rules::addRookThreats(player->globalMoves,localMoves,0,0,square);
}
void Piece::print(){
	display();
}
