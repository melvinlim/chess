#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
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
  extern Board *boardptr;
	bool checked(const Player *,const Square &);
	bool verify(const enum Color &,const Move &);
	bool verifyRook(const Move &);
	bool verifyBishop(const Move &);
	bool verifyKnight(const Move &);
	bool verifyQueen(const Move &);
	bool verifyKing(const Move &);
	bool verifyColor(const Piece *,const enum Color &);
	bool verifySrc(const Coord &);
	bool verifyDst(const Coord &);
	void updateMoveList(Stack<Move *> *,const Square &,const Square &);
	void addLegalMove(Stack<Move *> *,const Square &,const Square &);
	void addKingMoves(Stack<Move *> *,Square *);
	void addQueenMoves(Stack<Move *> *,Square *);
	void addBishopMoves(Stack<Move *> *,Square *);
	void addKnightMoves(Stack<Move *> *,Square *);
	void addRookMoves(Stack<Move *> *,Square *);
	void addPawnMoves(Stack<Move *> *,Square *,int);
}
#endif
