#include<string>
#include"board.h"
#include"square.h"
#include"defs.h"
class Game{
private:
	string str;
	Board *board;
	Move move;
	bool running;
public:
	Game();
	void step();
	void prompt(Move &);
	int getCoord(string,Move &);
	Square *coordToSquare(string,Coord &);
	void start();
};
