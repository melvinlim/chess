#include"piece.h"
using namespace std;
Piece::Piece(Color color){
	this->color=color;
	if(color==White){
		forwardDirection=-1;
	}else{
		forwardDirection=1;
	}
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
void Pawn::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addPawnThreats(threats,square,forwardDirection);
}
void King::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addKingThreats(threats,square);
}
void Queen::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addQueenThreats(threats,square);
}
void Knight::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addKnightThreats(threats,square);
}
void Bishop::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addBishopThreats(threats,square);
}
void Rook::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	Rules::addRookThreats(threats,square);
}
void Piece::print(){
	display();
}
