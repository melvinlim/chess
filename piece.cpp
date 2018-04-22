#include"piece.h"
using namespace std;
Piece::Piece(Color color){
		this->color=color;
}
void Piece::display(){
	printf("%s",self.data());
}
/*
void Piece::addThreats(Collection<Square *> *threats){
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
*/
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
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
void King::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
void Queen::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
void Knight::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
void Bishop::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
void Rook::addThreats(Collection<Square *> *threats){
	printf("%d\n",type);
	threats->add(square);
//	threats->add(rules.addThreats(threats,type));
}
