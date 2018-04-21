#include"piece.h"
using namespace std;
Piece::Piece(Color color){
		this->color=color;
}
void Piece::display(){
	printf("%s",self.data());
}
King::King(Color color):Piece(color){
	switch(color){
		case White:
			self=" K";
		break;
		case Black:
			self=" k";
		break;
	};
}
Pawn::Pawn(Color color):Piece(color){
	switch(color){
		case White:
			self=" P";
		break;
		case Black:
			self=" p";
		break;
	};
}
Queen::Queen(Color color):Piece(color){
	switch(color){
		case White:
			self=" Q";
		break;
		case Black:
			self=" q";
		break;
	};
}
