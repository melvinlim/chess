#include<string>
#include"board.h"
#include"square.h"
#include"player.h"
#include"rules.h"
#include"defs.h"
#include<list>
//class Move;
class Game{
private:
	bool valid;
	string str;
	Player *players[2];
	Board *board;
	Player *p1,*p2,*activePlayer;
	Move currentMove;
	bool running;
	int moveNumber;
	std::list<Move *> moveRecord;
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
	void printMoveList();
	bool isValidMove(const Move &);
	void addToRecord(const Move &);
	void testMove(const char *,const char *);
  void updateValidity(Player *);
};
