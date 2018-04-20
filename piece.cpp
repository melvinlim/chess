using namespace std;
enum Color{White,Black};
class Piece{
public:
	string self;
	void display(){
		printf("%s",self.data());
	}
};
class King:public Piece{
public:
	enum Color color;
	int location;
	King(Color color,int location){
		this->color=color;
		this->location=location;
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
