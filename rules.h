#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"board.h"
#include"piece.h"
#include<string>
//using namespace std;
class Board;
class Piece;
namespace Rules{
	bool verify(const enum Color &,const Board *,const Move &);
	bool verifyRook(const Board *,const Move &);
	bool verifyBishop(const Board *,const Move &);
	bool verifyKnight(const Board *,const Move &);
	bool verifyQueen(const Board *,const Move &);
	bool verifyKing(const Board *,const Move &);
	bool verifyColor(const Piece *,const enum Color &);
	bool verifySrc(const Board *,const Coord &);
	bool verifyDst(const Board *,const Coord &);
}
#endif
