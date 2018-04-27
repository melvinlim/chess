#ifndef _RULES_H
#define _RULES_H
#include"defs.h"
#include"board.h"
#include"piece.h"
#include"square.h"
#include"player.h"
#include<string>
class Player;
class Square;
class Board;
class Piece;
namespace Rules{
	bool checked(const Player *);
	bool verify(const enum Color &,const Board *,const Move &);
	bool verifyRook(const Board *,const Move &);
	bool verifyBishop(const Board *,const Move &);
	bool verifyKnight(const Board *,const Move &);
	bool verifyQueen(const Board *,const Move &);
	bool verifyKing(const Board *,const Move &);
	bool verifyColor(const Piece *,const enum Color &);
	bool verifySrc(const Board *,const Coord &);
	bool verifyDst(const Board *,const Coord &);
	void updateAllLists(Collection<Square *> *,Collection<Square *> *,Collection<Square *> *,Collection<Square *> *,Square *);
	void addBothLegalMoves(Collection<Square *> *,Collection<Square *> *,Square *);
	void addBothThreats(Collection<Square *> *,Collection<Square *> *,Square *);
	void addKingThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *);
	void addQueenThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *);
	void addBishopThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *);
	void addKnightThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *);
	void addRookThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *);
	void addPawnThreats(Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,Collection<Move *> *,const Square *,int);
}
#endif
