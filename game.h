#include<string>
#include"board.h"
#include"square.h"
#include"player.h"
#include"utility.h"
#include"rules.h"
#include"defs.h"
class Game{
private:
	bool valid;
	string str;
	Board *board;
	Rules rules;
	Utility utility;
	Player *p1,*p2,*activePlayer;
	Move move;
	bool running;
public:
	Game();
	void step();
	void step(Player *);
	void prompt(Move &);
	int getCoord(string,Move &);
	Square *coordToSquare(string,Coord &);
	void start();
};
