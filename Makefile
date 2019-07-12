DEBUGFLAGS= -Wall -pedantic-errors -g  
OPTFLAGS= -Wall -pedantic-errors -O2 -O3

2048: Game.o Board.o GameInput.o AIinput.o main.o Tile.o Display.o randomNum.o fTimer.o
	g++ $(OPTFLAGS) Game.o Board.o GameInput.o AIinput.o main.o Tile.o Display.o randomNum.o fTimer.o -o 2048 -lncurses
	rm *.o

2048-debug: Game_d.o Board_d.o GameInput_d.o main_d.o Tile_d.o Display_d.o randomNum_d.o AIinput_d.o
	g++ $(DEBUGFLAGS) Game_d.o Board_d.o GameInput_d.o AIinput_d.o main_d.o Tile_d.o Display_d.o randomNum_d.o -o 2048-debug -lncurses

Game.o: Game.cpp Game.h
	g++ $(OPTFLAGS) -c Game.cpp

Game_d.o: Game.cpp Game.h
	g++ $(DEBUGFLAGS) -c Game.cpp -o Game_d.o

GameInput.o: GameInput.cpp GameInput.h
	g++ $(OPTFLAGS) -c GameInput.cpp -lncurses 

GameInput_d.o: GameInput.cpp GameInput.h
	g++ $(DEBUGFLAGS) -c GameInput.cpp -o GameInput_d.o -lncurses

AIinput.o: AIinput.cpp AIinput.h GameInput.h
	g++ $(OPTFLAGS) -c AIinput.cpp

AIinput_d.o: AIinput.cpp AIinput.h GameInput.h
	g++ $(DEBUGFLAGS) -c AIinput.cpp -o AIinput_d.o

Board.o: Board.cpp Board.h Move.h
	g++ $(OPTFLAGS) -c Board.cpp 
	
Board_d.o: Board.cpp Board.h Move.h
	g++ $(DEBUGFLAGS) -c Board.cpp -o Board_d.o

Display.o: Display.cpp Display.h
	g++ $(OPTFLAGS) -c Display.cpp -lncurses

Display_d.o: Display.cpp Display.h
	g++ $(DEBUGFLAGS) -c Display.cpp -o Display_d.o -lncurses

Tile.o: Tile.cpp Tile.h
	g++ $(OPTFLAGS) -c Tile.cpp Tile.h 

Tile_d.o: Tile.cpp Tile.h
	g++ $(DEBUGFLAGS) -c Tile.cpp -o Tile_d.o

 randomNum.o: randomNum.cpp randomNum.h
	g++ $(OPTFLAGS) -c randomNum.cpp

randomNum_d.o: randomNum.cpp randomNum.h
	g++ $(DEBUGFLAGS) -c randomNum.cpp -o randomNum_d.o

main.o: main.cpp	
	g++ $(OPTFLAGS) -c main.cpp 

main_d.o: main.cpp
	g++ $(DEBUGFLAGS) -c main.cpp -o main_d.o

clean-obj:
	rm -rf *.o 2048

