#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"move.h"
#include"stack.h"
#include"board.h"
#include"piece.h"
#include"square.h"
#include"player.h"
#include"utility.h"
#include<string>
class Player;
class Square;
class Board;
class Piece;
namespace Rules{
	bool checked(const Player *);
	bool checked(const Player *,Square *);
	bool verify(const enum Color &,const Board *,const Move &);
	bool verifyRook(const Board *,const Move &);
	bool verifyBishop(const Board *,const Move &);
	bool verifyKnight(const Board *,const Move &);
	bool verifyQueen(const Board *,const Move &);
	bool verifyKing(const Board *,const Move &);
	bool verifyColor(const Piece *,const enum Color &);
	bool verifySrc(const Board *,const Coord &);
	bool verifyDst(const Board *,const Coord &);
	void updateAllLists(Stack<Move *> *,Square *,Square *);
	void addBothLegalMoves(Stack<Move *> *,Square *,Square *);
	void addKingMoves(Board *,Stack<Move *> *,Square *);
	void addQueenMoves(Board *,Stack<Move *> *,Square *);
	void addBishopMoves(Board *,Stack<Move *> *,Square *);
	void addKnightMoves(Board *,Stack<Move *> *,Square *);
	void addRookMoves(Board *,Stack<Move *> *,Square *);
	void addPawnMoves(Board *,Stack<Move *> *,Square *,int);
}
#endif
