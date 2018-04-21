#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"board.h"
#include"piece.h"
#include<string>
using namespace std;
class Rules{
public:
	bool verify(const enum Color &,Board *,const Move &);
	bool verifyColor(Piece *,const enum Color &);
	bool verifySrc(const Board *,const Coord &);
	bool verifyDst(const Board *,const Coord &);
};
#endif
