#include"piece.h"
using namespace std;
void updatePieceHelper(Piece *piece){
	if(piece->removed)	return;
	piece->player->globalMoves->remove(piece->localMoves);
	delete piece->localMoves;
	piece->localMoves=new Collection<Move *>(piece);
	piece->addThreats(piece->player->globalMoves);
}
void Piece::removePiece(){
	removed=true;
	player->globalMoves->remove(localMoves);
	square->attackers->remove(this);
	square->piece=0;
	delete localMoves;
	localMoves=new Collection<Move *>(this);
	square->attackers->list.apply(updatePieceHelper);
}
void Piece::place(Square *targetSquare){
	removed=false;
	square=targetSquare;
	square->piece=this;
	addThreats(this->player->globalMoves);
	square->attackers->list.apply(updatePieceHelper);
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
	Rules::addPawnThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square,forwardDirection);
}
void King::addThreats(Collection<Move *> *allThreats){
	Rules::addKingThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square);
}
void Queen::addThreats(Collection<Move *> *allThreats){
	Rules::addQueenThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square);
}
void Knight::addThreats(Collection<Move *> *allThreats){
	Rules::addKnightThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square);
}
void Bishop::addThreats(Collection<Move *> *allThreats){
	Rules::addBishopThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square);
}
void Rook::addThreats(Collection<Move *> *allThreats){
	Rules::addRookThreats(player->globalMoves,localMoves,player->globalAttacks,localAttacks,square);
}
void Piece::print(){
	display();
}
