OPTFLAGS= -Wall -pedantic-errors -O2 -O3 

2048: Game.o Board.o GameInput.o AIinput.o main.o Display.o randomNum.o mainMenu.o
	g++ $(OPTFLAGS) Game.o Board.o GameInput.o AIinput.o main.o Display.o randomNum.o mainMenu.o -o 2048 -lncurses

mainMenu.o: mainMenu.cpp mainMenu.h
	g++ $(OPTFLAGS) -c mainMenu.cpp

Game.o: Game.cpp Game.h
	g++ $(OPTFLAGS) -c Game.cpp

GameInput.o: GameInput.cpp GameInput.h
	g++ $(OPTFLAGS) -c GameInput.cpp -lncurses 

AIinput.o: AIinput.cpp AIinput.h GameInput.h
	g++ $(OPTFLAGS) -c AIinput.cpp

Board.o: Board.cpp Board.h 
	g++ $(OPTFLAGS) -c Board.cpp 
	
Display.o: Display.cpp Display.h
	g++ $(OPTFLAGS) -c Display.cpp -lncurses

randomNum.o: randomNum.cpp randomNum.h
	g++ $(OPTFLAGS) -c randomNum.cpp

main.o: main.cpp	
	g++ $(OPTFLAGS) -c main.cpp 

clean-obj:
	rm -rf *.o 2048

