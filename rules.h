#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"board.h"
#include"piece.h"
#include"square.h"
#include<string>
class Square;
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
	void addKingThreats(Collection<Square *> *,const Square *);
	void addQueenThreats(Collection<Square *> *,const Square *);
	void addBishopThreats(Collection<Square *> *,const Square *);
	void addKnightThreats(Collection<Square *> *,const Square *);
	void addRookThreats(Collection<Square *> *,const Square *);
	void addPawnThreats(Collection<Square *> *,const Square *,int);
}
#endif
