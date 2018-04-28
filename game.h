#include<string>
#include"board.h"
#include"square.h"
#include"player.h"
#include"rules.h"
#include"defs.h"
class Game{
private:
	bool valid;
	string str;
	Player *players[2];
	Board *board;
	Player *p1,*p2,*activePlayer;
	Move move;
	bool running;
public:
	Game();
	void reset();
	void step();
	void step(Player *);
	bool gameOver(Player *);
	void prompt(Move &);
	int getCoord(string,Move &);
	Square *coordToSquare(string,Coord &);
	void start();
	void test();
	void testMove(const char *,const char *);
};
