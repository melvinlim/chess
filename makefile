CC = g++
CFLAGS = -Wall -g -c
LFLAGS = -Wall -g -o chess
chess:	main.o board.o square.o piece.o game.o
	$(CC) $(LFLAGS) main.o board.o square.o piece.o game.o
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
clean:
	rm -f chess *.o a.out
