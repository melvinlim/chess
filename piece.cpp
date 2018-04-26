#include"piece.h"
using namespace std;
void updatePieceHelper(Piece *piece){
	piece->player->legalMoves->remove(piece->legalMoves);
	piece->legalMoves->clear();
	piece->player->threats->remove(piece->threats);
	piece->threats->clear();
	piece->addThreats(piece->player->threats);
}
void removePieceHelper(Square *square){
	square->attackers->list.apply(updatePieceHelper);
}
void Piece::removePiece(){
	player->legalMoves->remove(legalMoves);
	player->threats->remove(threats);
	square->attackers->remove(this);
	square->piece=0;
	threats->removePiece(this);
	threats->list.apply(removePieceHelper);
	threats->clear();
	legalMoves->clear();
	square->attackers->list.apply(updatePieceHelper);
}
void Piece::place(){
	addThreats(player->threats);
	square->attackers->list.apply(updatePieceHelper);
}
Piece::Piece(Color color){
	this->color=color;
	if(color==White){
		forwardDirection=-1;
	}else{
		forwardDirection=1;
	}
	threats=new Collection<Square *>(this);
	legalMoves=new Collection<Square *>(this);
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
void Pawn::addThreats(Collection<Square *> *allThreats){
	Rules::addPawnThreats(player->legalMoves,legalMoves,allThreats,threats,square,forwardDirection);
}
void King::addThreats(Collection<Square *> *allThreats){
	Rules::addKingThreats(player->legalMoves,legalMoves,allThreats,threats,square);
}
void Queen::addThreats(Collection<Square *> *allThreats){
	Rules::addQueenThreats(player->legalMoves,legalMoves,allThreats,threats,square);
}
void Knight::addThreats(Collection<Square *> *allThreats){
	Rules::addKnightThreats(player->legalMoves,legalMoves,allThreats,threats,square);
}
void Bishop::addThreats(Collection<Square *> *allThreats){
	Rules::addBishopThreats(player->legalMoves,legalMoves,allThreats,threats,square);
}
void Rook::addThreats(Collection<Square *> *allThreats){
	Rules::addRookThreats(player->legalMoves,legalMoves,allThreats,threats,square);
}
void Piece::print(){
	display();
}
