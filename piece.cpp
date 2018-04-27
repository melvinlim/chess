#include"piece.h"
using namespace std;
void updatePieceHelper(Piece *piece){
	piece->player->globalMoves->remove(piece->localMoves);
	piece->localMoves->clear();
	piece->addThreats(piece->player->globalMoves);
}
void Piece::removePiece(){
	player->globalMoves->remove(localMoves);
	square->attackers->remove(this);
	square->piece=0;
	//threats->removePiece(this);
	localMoves->clear();
	square->attackers->list.apply(updatePieceHelper);
}
void Piece::place(){
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
void King::place(){
	Piece::place();
	player->kingSquare=square;
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
