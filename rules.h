#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"move.h"
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
	void updateAllLists(Collection<Move *> *,Square *,Square *);
	void addBothLegalMoves(Collection<Move *> *,Square *,Square *);
	void addKingMoves(Collection<Move *> *,Square *);
	void addQueenMoves(Collection<Move *> *,Square *);
	void addBishopMoves(Collection<Move *> *,Square *);
	void addKnightMoves(Collection<Move *> *,Square *);
	void addRookMoves(Collection<Move *> *,Square *);
	void addPawnMoves(Collection<Move *> *,Square *,int);
}
#endif
