CC = g++
CFLAGS = -Wall -g -c
LFLAGS = -Wall -g -o chess
chess:	main.o board.o square.o piece.o game.o player.o utility.o rules.o
	$(CC) $(LFLAGS) main.o board.o square.o piece.o game.o player.o utility.o rules.o
main:		main.cpp
	$(CC) $(CFLAGS) main.cpp
board:	board.cpp defs.h square.h
	$(CC) $(CFLAGS) board.cpp
square:	square.cpp piece.h
	$(CC) $(CFLAGS) square.cpp
piece:	piece.cpp defs.h
	$(CC) $(CFLAGS) piece.cpp
game:		game.cpp board.h
	$(CC) $(CFLAGS) game.cpp
player:	player.cpp defs.h board.h
	$(CC) $(CFLAGS) player.cpp
utility:	utility.cpp defs.h
	$(CC) $(CFLAGS) utility.cpp
rules:	rules.cpp defs.h
	$(CC) $(CFLAGS) rules.cpp
clean:
	rm -f chess *.o a.out
