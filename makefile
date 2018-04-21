chess:	main.o board.o square.o piece.o game.o
	g++ -o chess main.o board.o square.o piece.o game.o
main:		main.cpp
	g++ -c main.cpp
board:	board.cpp defs.h square.h
	g++ -c board.cpp
square:	square.cpp piece.h
	g++ -c square.cpp
piece:	piece.cpp defs.h
	g++ -c piece.cpp
game:		game.cpp board.h
	g++ -c game.cpp
clean:
	rm -f chess *.o a.out
