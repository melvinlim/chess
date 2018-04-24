#include"piece.h"
using namespace std;
void updatePieceHelper(Piece *piece){
	piece->player->threats->remove(piece->threats);
	piece->threats->clear();
	piece->addThreats(piece->player->threats);
}
void removePieceHelper(Square *square){
	square->attackers->list.apply(updatePieceHelper);
	square->attackers->clear();
}
void Piece::removePiece(){
	player->threats->remove(threats);
	square->attackers->remove(this);
	square->piece=0;
	threats->list.apply(removePieceHelper);
	threats->clear();
	square->attackers->list.apply(updatePieceHelper);
}
void Piece::place(){
	printf("pp\n");
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
	printf("kp\n");
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
	printf("%d\n",type);
	Rules::addPawnThreats(allThreats,threats,square,forwardDirection);
}
void King::addThreats(Collection<Square *> *allThreats){
	printf("%d\n",type);
	Rules::addKingThreats(allThreats,threats,square);
}
void Queen::addThreats(Collection<Square *> *allThreats){
	printf("%d\n",type);
	Rules::addQueenThreats(allThreats,threats,square);
}
void Knight::addThreats(Collection<Square *> *allThreats){
	printf("%d\n",type);
	Rules::addKnightThreats(allThreats,threats,square);
}
void Bishop::addThreats(Collection<Square *> *allThreats){
	printf("%d\n",type);
	Rules::addBishopThreats(allThreats,threats,square);
}
void Rook::addThreats(Collection<Square *> *allThreats){
	printf("%d\n",type);
	Rules::addRookThreats(allThreats,threats,square);
}
void Piece::print(){
	display();
}
