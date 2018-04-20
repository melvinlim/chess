#include"board.h"
using namespace std;
enum Color{White,Black};
class Piece{
public:
	enum Color color;
	Square *square;
	string self;
	Piece(Color color){
		this->color=color;
	}
	void display(){
		printf("%s",self.data());
	}
};
class King:public Piece{
public:
	King(Color color):Piece(color){
		switch(color){
			case White:
				self=" K";
			break;
			case Black:
				self=" k";
			break;
		};
	}
};
class Pawn:public Piece{
public:
	Pawn(Color color):Piece(color){
		switch(color){
			case White:
				self=" P";
			break;
			case Black:
				self=" p";
			break;
		};
	}
};
class Queen:public Piece{
public:
	Queen(Color color):Piece(color){
		switch(color){
			case White:
				self=" Q";
			break;
			case Black:
				self=" q";
			break;
		};
	}
};
