CPPFLAGS= -Wall -pedantic-errors -g -pg 

all:
	make 2048
	cd Tests && $(MAKE) all
	make clean-obj


.PHONY: runTests
runTests: Tests/test-board Tests/test-tile Tests/test-mover Tests/test-factory
	cd Tests && $(MAKE) all
	cd Tests && ./test-board
	./test-tile
	./test-mover
	./test-factory

2048: Game.o Board.o GameInput.o main.o Tile.o Display.o randomNum.o 
	g++ $(CPPFLAGS) Game.o Board.o GameInput.o main.o Tile.o Display.o randomNum.o -o 2048 -lncurses

Game.o: Game.cpp Game.h
	g++ $(CPPFLAGS) -c Game.cpp

GameInput.o: GameInput.cpp GameInput.h
	g++ $(CPPFLAGS) -c GameInput.cpp -lncurses

Board.o: Board.cpp Board.h
	g++ $(CPPFLAGS) -c Board.cpp

Display.o: Display.cpp Display.h
	g++ $(CPPFLAGS) -c Display.cpp -lncurses

Tile.o: Tile.cpp Tile.h
	g++ $(CPPFLAGS) -c Tile.cpp

randomNum.o: randomNum.cpp randomNum.h
	g++ $(CPPFLAGS) -c randomNum.cpp

clean-obj:
	rm -rf *.o 2048

