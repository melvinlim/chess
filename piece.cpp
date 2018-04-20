using namespace std;
enum Color{White,Black};
class Piece{
public:
	enum Color color;
	int location;
	string self;
	Piece(Color color,int location){
		this->color=color;
		this->location=location;
	}
	void display(){
		printf("%s",self.data());
	}
};
class King:public Piece{
public:
	King(Color color,int location):Piece(color,location){
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
	Pawn(Color color,int location):Piece(color,location){
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
	Queen(Color color,int location):Piece(color,location){
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
