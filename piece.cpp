#include"piece.h"
using namespace std;
Piece::Piece(Color color){
		this->color=color;
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
}
Pawn::Pawn(Color color):Piece(color){
	setSelf(" P");
}
Queen::Queen(Color color):Piece(color){
	setSelf(" Q");
}
Knight::Knight(Color color):Piece(color){
	setSelf(" N");
}
Bishop::Bishop(Color color):Piece(color){
	setSelf(" B");
}
Rook::Rook(Color color):Piece(color){
	setSelf(" R");
}
