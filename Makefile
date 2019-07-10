CPPFLAGS= -Wall -pedantic-errors -g -pg 
OPTFLAGS= -Wall -pedantic-errors -O3

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

2048-opt: Game-opt.o Board-opt.o GameInput-opt.o main-opt.o Tile-opt.o Display-opt.o randomNum-opt.o
	g++ $(OPTFLAGS) Game-opt.o Board-opt.o GameInput-opt.o main-opt.o Tile-opt.o Display-opt.o randomNum-opt.o -o 2048 -lncurses

2048-debug: Game.o Board.o GameInput.o main.o Tile.o Display.o randomNum.o 
	g++ $(CPPFLAGS) Game.o Board.o GameInput.o main.o Tile.o Display.o randomNum.o -o 2048-debug -lncurses

Game-opt.o: Game.cpp Game.h
	g++ $(OPTFLAGS) -c Game.cpp -o Game-opt.o

Game.o: Game.cpp Game.h
	g++ $(CPPFLAGS) -c Game.cpp

GameInput-opt.o: GameInput.cpp GameInput.h
	g++ $(OPTFLAGS) -c GameInput.cpp -lncurses -o GameInput-opt.o

GameInput.o: GameInput.cpp GameInput.h
	g++ $(CPPFLAGS) -c GameInput.cpp -lncurses

Board-opt.o: Board.cpp Board.h
	g++ $(OPTFLAGS) -c Board.cpp -o Board-opt.o
	
Board.o: Board.cpp Board.h
	g++ $(CPPFLAGS) -c Board.cpp

Display-opt.o: Display.cpp Display.h
	g++ $(OPTFLAGS) -c Display.cpp -lncurses -o Display-opt.o

Display.o: Display.cpp Display.h
	g++ $(CPPFLAGS) -c Display.cpp -lncurses

Tile-opt.o: Tile.cpp Tile.h
	g++ $(OPTFLAGS) -c Tile.cpp -o Tile-opt.o

Tile.o: Tile.cpp Tile.h
	g++ $(CPPFLAGS) -c Tile.cpp

randomNum-opt.o: randomNum.cpp randomNum.h
	g++ $(OPTFLAGS) -c randomNum.cpp -o randomNum-opt.o

randomNum.o: randomNum.cpp randomNum.h
	g++ $(CPPFLAGS) -c randomNum.cpp

main-opt.o: main.cpp	
	g++ $(OPTFLAGS) -c main.cpp -o main-opt.o

clean-obj:
	rm -rf *.o 2048

