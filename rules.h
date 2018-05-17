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
	void addKingThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *);
	void addQueenThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *);
	void addBishopThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *);
	void addKnightThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *);
	void addRookThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *);
	void addPawnThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Square *,int);
}
#endif
