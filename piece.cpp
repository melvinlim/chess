enum Color{White,Black};
class Piece{
public:
	virtual void display()=0;
};
class King:public Piece{
public:
	char self;
	enum Color color;
	int location;
	King(Color color,int location){
		this->color=color;
		this->location=location;
		switch(color){
			case White:
				self='K';
			break;
			case Black:
				self='k';
			break;
		};
	}
	void display(){
		printf("%c",self);
	}
};
