CXX =				g++
CXXFLAGS =	-Wall -g
LFLAGS =		-Wall -g -o chess
OBJECTS =		main.o board.o square.o piece.o game.o player.o utility.o rules.o
chess:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
main:			main.cpp
	$(CXX) $(CXXFLAGS) main.cpp
board:		board.cpp defs.h square.h piece.h
	$(CXX) $(CXXFLAGS) board.cpp
square:		square.cpp piece.h
	$(CXX) $(CXXFLAGS) square.cpp
piece:		piece.cpp defs.h
	$(CXX) $(CXXFLAGS) piece.cpp
game:			game.cpp board.h square.h player.h utility.h rules.h defs.h
	$(CXX) $(CXXFLAGS) game.cpp
player:		player.cpp defs.h piece.h
	$(CXX) $(CXXFLAGS) player.cpp
utility:	utility.cpp defs.h
	$(CXX) $(CXXFLAGS) utility.cpp
rules:		rules.cpp defs.h board.h piece.h
	$(CXX) $(CXXFLAGS) rules.cpp
clean:
	rm -f chess *.o a.out
